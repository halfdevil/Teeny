#include "Scene/Scene.h"

int32_t Scene::addNode(int32_t parent)
{
	int32_t node = (int32_t)mSceneData.hierarchy.size();

	mSceneData.localTransforms.push_back(glm::mat4(1.0f));
	mSceneData.globalTransforms.push_back(glm::mat4(1.0f));

	mSceneData.hierarchy.push_back({
	  .parent = parent,
	  .lastSibling = -1
		});

	if (parent > -1)
	{
		int32_t s = mSceneData.hierarchy[parent].firstChild;
		if (s == -1)
		{
			mSceneData.hierarchy[parent].firstChild = node;
			mSceneData.hierarchy[node].lastSibling = node;
		}
		else
		{
			int32_t dest = mSceneData.hierarchy[s].lastSibling;
			if (dest <= -1)
			{
				dest = s;
				while (mSceneData.hierarchy[dest].lastSibling != -1)
					dest = mSceneData.hierarchy[dest].nextSibling;
			}

			mSceneData.hierarchy[dest].nextSibling = node;
			mSceneData.hierarchy[s].lastSibling = node;
		}
	}

	int32_t level = (parent > -1) ? mSceneData.hierarchy[parent].level + 1 : -1;

	mSceneData.hierarchy[node].level = level;
	mSceneData.hierarchy[node].nextSibling = -1;
	mSceneData.hierarchy[node].firstChild = -1;

	return node;
}

int32_t Scene::findNodeByName(const std::string& name)
{
	for (int32_t i = 0; i < (int32_t)mSceneData.localTransforms.size(); i++)
	{
		if (mSceneData.nodeNameMap.contains(i))
		{
			int32_t index = mSceneData.nodeNameMap.at(i);
			if (index > -1)
			{
				if (mSceneData.nodeNames[index] == name)
				{
					return (int32_t)i;
				}
			}
		}
	}

	return -1;
}

std::string Scene::getNodeName(int32_t node)
{
	int32_t index = mSceneData.nodeNameMap.contains(node) ? mSceneData.nodeNameMap.at(node) : -1;
	return (index > -1) ? mSceneData.nodeNames[index] : std::string();
}

void Scene::setNodeName(int32_t node, const std::string& name)
{
	int32_t index = mSceneData.nodeNameMap.contains(node) ? mSceneData.nodeNameMap.at(node) : -1;
	if (index > -1)
	{
		mSceneData.nodeNames[index] = name;
	}
	else
	{
		index = (int32_t)mSceneData.nodeNames.size();
		mSceneData.nodeNames.push_back(name);
		mSceneData.nodeNameMap.insert(std::pair(node, index));
	}
}

void Scene::markNodeAsDirty(int32_t node)
{
	int32_t level = mSceneData.hierarchy[node].level;
	mSceneData.dirtyNodes[level].push_back(node);

	int32_t s = mSceneData.hierarchy[node].firstChild;
	while (s != -1)
	{
		s = mSceneData.hierarchy[s].nextSibling;
		markNodeAsDirty(s);
	}
}

void Scene::recalculateGlobalTransforms()
{
	if (!mSceneData.dirtyNodes[0].empty())
	{
		int32_t p = mSceneData.dirtyNodes[0][0];
		mSceneData.globalTransforms[p] = mSceneData.localTransforms[p];
		mSceneData.dirtyNodes[0].clear();
	}

	for (uint32_t i = 0; i < kMaxNodeLevel && !mSceneData.dirtyNodes[i].empty(); i++)
	{
		for (const auto& n : mSceneData.dirtyNodes[i])
		{
			int32_t p = mSceneData.hierarchy[n].parent;
			mSceneData.globalTransforms[n] = mSceneData.globalTransforms[p] * mSceneData.localTransforms[n];
		}

		mSceneData.dirtyNodes[i].clear();
	}
}

SceneRenderer::SceneRenderer()
	: mMaterialsBuffer(GL_SHADER_STORAGE_BUFFER),
	mModelMatricesBuffer(GL_SHADER_STORAGE_BUFFER),
	mCommandBuffer(GL_DRAW_INDIRECT_BUFFER)
{
}

SceneRenderer::~SceneRenderer()
{
	destroy();
}

void SceneRenderer::create(const Scene& scene)
{
	auto lodIndicesCount = [](const MeshData& meshData, uint32_t meshIndex, uint32_t lod) {
		const auto& mesh = meshData.meshes[meshIndex];
		return mesh.lodOffset[lod + 1] - mesh.lodOffset[lod];
	};

	VertexFormat format{ {
	  {.index = 0, .binding = 0, .offset = 0, .format = GL_FLOAT, .size = 12 },
	  {.index = 1, .binding = 0, .offset = 12, .format = GL_FLOAT, .size = 12 },
	  {.index = 2, .binding = 0, .offset = 24, .format = GL_FLOAT, .size = 8 }
	} };

	const auto& sceneData = scene.getData();
	const auto& meshData = sceneData.meshData;

	mVertexArray.create();
	mVertexArray.activate();

	mVertexArray.addVertexBuffer(format, 0, meshData.header.vertexDataSize / format.getSize(),
		meshData.vertexData.data());

	mVertexArray.setIndexBuffer(GL_UNSIGNED_INT, meshData.header.indexDataSize / sizeof(uint32_t),
		meshData.indexData.data());

	mMaterialsBuffer.create(sizeof(Material) * (uint32_t)sceneData.materials.size(),
		sceneData.materials.data(), 0);

	mModelMatricesBuffer.create(sizeof(glm::mat4) * (uint32_t)sceneData.drawDatas.size(),
		nullptr, GL_DYNAMIC_STORAGE_BIT);

	mCommandBuffer.create(sizeof(IndirectDrawCommand) * (uint32_t)sceneData.drawDatas.size() +
		sizeof(GLsizei), nullptr, GL_DYNAMIC_STORAGE_BIT);

	std::vector<uint8_t> drawCommands;
	drawCommands.resize(sizeof(IndirectDrawCommand) * sceneData.drawDatas.size() +
		sizeof(GLsizei));

	IndirectDrawCommand* command = std::launder(reinterpret_cast<IndirectDrawCommand*>
		(drawCommands.data() + sizeof(GLsizei)));

	for (size_t i = 0; i < sceneData.drawDatas.size(); i++)
	{
		const uint32_t meshIndex = sceneData.drawDatas[i].meshIndex;
		const uint32_t lod = sceneData.drawDatas[i].lod;

		*command++ = {
		  .count = lodIndicesCount(meshData, meshIndex, lod),
		  .instanceCount = 1,
		  .firstIndex = sceneData.drawDatas[i].indexOffset,
		  .baseVertex = sceneData.drawDatas[i].vertexOffset,
		  .baseInstance = sceneData.drawDatas[i].materialIndex
		};
	}

	mCommandBuffer.upload(0, (uint32_t)drawCommands.size(), drawCommands.data());

	std::vector<glm::mat4> matrices(sceneData.drawDatas.size());
	uint32_t index = 0;

	for (const auto& drawData : sceneData.drawDatas)
	{
		matrices[index++] = sceneData.globalTransforms[drawData.transformIndex];
	}

	mModelMatricesBuffer.upload(0, (uint32_t)sceneData.drawDatas.size() *
		sizeof(glm::mat4), matrices.data());

	maxDrawCount = (uint32_t)sceneData.drawDatas.size();
}

void SceneRenderer::destroy()
{
	mVertexArray.destroy();
	mMaterialsBuffer.destroy();
	mModelMatricesBuffer.destroy();
	mCommandBuffer.destroy();
}

void SceneRenderer::draw()
{
	mVertexArray.activate();
	mMaterialsBuffer.bind(kBufferIndex_Materials);
	mModelMatricesBuffer.bind(kBufferIndex_ModelMatrices);
	mCommandBuffer.bind();
	mCommandBuffer.bindAs(GL_PARAMETER_BUFFER);
	mVertexArray.drawIndirect(GL_TRIANGLES, 0, maxDrawCount, 0);
}
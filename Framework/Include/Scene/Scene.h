#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Graphics/VertexArray.h"
#include "Graphics/VertexFormat.h"
#include "Scene/Mesh.h"
#include "Scene/Material.h"

constexpr const uint32_t kMaxNodeLevel = 16;
constexpr const uint32_t kBufferIndex_ModelMatrices = 1;
constexpr const uint32_t kBufferIndex_Materials = 2;

struct DrawData
{
	uint32_t meshIndex{ 0 };
	uint32_t materialIndex{ 0 };
	uint32_t lod{ 0 };
	uint32_t indexOffset{ 0 };
	uint32_t vertexOffset{ 0 };
	uint32_t transformIndex{ 0 };
};

struct SceneHierarchy
{
	int32_t parent{ -1 };
	int32_t firstChild{ -1 };
	int32_t nextSibling{ -1 };
	int32_t lastSibling{ -1 };
	int32_t level{ -1 };
};

struct SceneData
{
	MeshData meshData;
	std::vector<glm::mat4> localTransforms;
	std::vector<glm::mat4> globalTransforms;
	std::vector<int32_t> dirtyNodes[kMaxNodeLevel];
	std::vector<SceneHierarchy> hierarchy;
	std::vector<DrawData> drawDatas;
	std::vector<Material> materials;
	std::vector<std::string> nodeNames;
	std::unordered_map<uint32_t, uint32_t> nodeMeshMap;
	std::unordered_map<uint32_t, uint32_t> nodeNameMap;
	std::unordered_map<uint32_t, uint32_t> nodeMaterialMap;
};

class Scene
{
public:

	const SceneData& getData() const
	{
		return mSceneData;
	}

	int32_t addNode(int32_t parent);
	int32_t findNodeByName(const std::string& name);

	std::string getNodeName(int32_t node);
	void setNodeName(int32_t node, const std::string& name);

	void markNodeAsDirty(int32_t node);
	void recalculateGlobalTransforms();

private:

	SceneData mSceneData;
};

struct IndirectDrawCommand
{
	GLuint count{ 0 };
	GLuint instanceCount{ 0 };
	GLuint firstIndex{ 0 };
	GLuint baseVertex{ 0 };
	GLuint baseInstance{ 0 };
};

class SceneRenderer
{
public:

	SceneRenderer();
	~SceneRenderer();

	void create(const Scene& scene);
	void destroy();
	void draw();

private:

	VertexArray mVertexArray;
	Buffer mMaterialsBuffer;
	Buffer mModelMatricesBuffer;
	Buffer mCommandBuffer;
	uint32_t maxDrawCount{ 0 };
};
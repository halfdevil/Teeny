#pragma once

#include <string>
#include <unordered_map>
#include <vector>

constexpr const int kMaxLODs = 8;
constexpr const int kMaxStreams = 8;

struct Mesh
{
	uint32_t lodCount{ 1 };
	uint32_t streamCount{ 0 };
	uint32_t indexOffset{ 0 };
	uint32_t vertexOffset{ 0 };
	uint32_t vertexCount{ 0 };
	uint32_t lodOffset[kMaxLODs];
	uint32_t streamOffset[kMaxStreams];
	uint32_t streamElementSize[kMaxStreams];
};

struct MeshHeader
{
	uint32_t meshCount{ 0 };
	uint32_t dataBlockStartOffset{ 0 };
	uint32_t indexDataSize{ 0 };
	uint32_t vertexDataSize{ 0 };
};

struct MeshData
{
	MeshHeader header;
	std::vector<uint32_t> indexData;
	std::vector<float> vertexData;
	std::vector<Mesh> meshes;
};

#pragma once

#include "Graphics/Buffer.h"
#include "Graphics/VertexFormat.h"

class VertexArray
{
public:

	VertexArray() = default;
	~VertexArray()
	{
		destroy();
	}

	const Buffer& getVertexBuffer(uint32_t index) const
	{
		return *mVertexBuffers[index].get();
	}

	const Buffer& getIndexBuffer() const
	{
		return *mIndexBuffer.get();
	}

	void create();
	void destroy();

	void addVertexBuffer(const VertexFormat& vertexFormat, uint32_t index,
		uint32_t numVertices, const void* data);

	void setIndexBuffer(GLenum indexFormat, uint32_t numIndices, const void* data);
	void draw(GLenum mode, uint32_t first, uint32_t count);
	void drawIndirect(GLenum mode, uint32_t drawCount, uint32_t maxDrawCount, uint32_t stride);
	void activate();

private:

	GLuint mHandle{ 0 };
	std::vector<std::unique_ptr<Buffer>> mVertexBuffers;
	std::unique_ptr<Buffer> mIndexBuffer{ nullptr };
};
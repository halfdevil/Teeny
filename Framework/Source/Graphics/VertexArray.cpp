#include "Graphics/VertexArray.h"
#include "Core/Core.h"

void VertexArray::create()
{
  glCreateVertexArrays(1, &mHandle);
  if (!mHandle)
  {
    EXIT("glCreateVertexArrays() failed");
  }
}

void VertexArray::destroy()
{
  if (mHandle)
  {
    glDeleteVertexArrays(1, &mHandle);
  }
}

void VertexArray::addVertexBuffer(const VertexFormat& vertexFormat, uint32_t index, 
    uint32_t numVertices, const void* data)
{
  auto buffer = std::make_unique<Buffer>(GL_ARRAY_BUFFER);
  buffer->create(vertexFormat.getSize() * numVertices, data, 0);

  glVertexArrayVertexBuffer(mHandle, index, buffer->getHandle(), 0, vertexFormat.getSize());

  for (const auto& element : vertexFormat.getElements())
  {
    glEnableVertexArrayAttrib(mHandle, element.index);
    glVertexArrayAttribFormat(mHandle, element.index, element.size, element.format, GL_FALSE, element.offset);
    glVertexArrayAttribBinding(mHandle, element.index, index);
  }

  mVertexBuffers.push_back(std::move(buffer));
}

void VertexArray::setIndexBuffer(GLenum indexFormat, uint32_t numIndices, const void* data)
{
  const auto indexSize = (indexFormat == GL_UNSIGNED_SHORT) ? 2 : 4;

  mIndexBuffer = std::make_unique<Buffer>(GL_ELEMENT_ARRAY_BUFFER);
  mIndexBuffer->create(indexSize * numIndices, data, 0);

  glVertexArrayElementBuffer(mHandle, mIndexBuffer->getHandle());
}

void VertexArray::draw(GLenum mode, uint32_t first, uint32_t count)
{
  glDrawArrays(mode, first, count);
}

void VertexArray::drawIndirect(GLenum mode, uint32_t drawCount, uint32_t maxDrawCount, uint32_t stride)
{
  glMultiDrawElementsIndirectCount(mode, GL_UNSIGNED_INT, (const void*)sizeof(GLsizei),
    (GLsizei)drawCount, (GLsizei)maxDrawCount, (GLsizei)stride);
}

void VertexArray::activate()
{
  glBindVertexArray(mHandle);
}
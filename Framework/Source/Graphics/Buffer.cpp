#include "Graphics/Buffer.h"
#include "Core/Core.h"

void Buffer::create(uint32_t size, const void* data, uint32_t flags)
{
  glCreateBuffers(1, &mHandle);
  if (!mHandle)
  {
    EXIT("glCreateBuffers() failed");
  }

  glNamedBufferStorage(mHandle, size, data, flags);
}

void Buffer::destroy()
{
  if (mHandle)
  {
    glDeleteBuffers(1, &mHandle);
  }
}

void Buffer::bind(uint32_t index)
{
  glBindBufferBase(mTarget, index, mHandle);
}

void Buffer::bindRange(uint32_t index, uint32_t offset, uint32_t size)
{
  glBindBufferRange(mTarget, index, mHandle, offset, size);
}

void Buffer::upload(uint32_t offset, uint32_t size, const void* data)
{
  glNamedBufferSubData(mHandle, offset, size, data);
}
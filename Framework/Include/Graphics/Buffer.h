#pragma once

#include "Core/StdHeaders.h"
#include <glad/glad.h>

class Buffer
{
public:

  Buffer(GLenum target)
    : mTarget(target)
  {
  }

  ~Buffer()
  {
    destroy();
  }

  GLuint getHandle() const
  {
    return mHandle;
  }

  void create(uint32_t size, const void* data, uint32_t flags);
  void destroy();

  void bind();
  void bindAs(GLenum target);
  
  void bind(uint32_t index);
  void bindRange(uint32_t index, uint32_t offset, uint32_t size);  
  void upload(uint32_t offset, uint32_t size, const void* data);

private:

  GLenum mTarget{ 0 };
  GLuint mHandle{ 0 };
};
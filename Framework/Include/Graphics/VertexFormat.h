#pragma once

#include "Core/StdHeaders.h"
#include "glad/glad.h"

struct VertexElement
{
  uint8_t index{ 0 };
  uint8_t binding{ 0 };
  uint8_t offset{ 0 };
  GLenum format{ GL_FLOAT };
  uint32_t size{ 0 };  
};

class VertexFormat
{
public:

  explicit VertexFormat(std::vector<VertexElement> elements);

  uint32_t getSize() const
  {
    return mSize;
  }

  const std::vector<VertexElement>& getElements() const
  {
    return mElements;
  }

private:

  std::vector<VertexElement> mElements;
  uint32_t mSize{ 0 };
};
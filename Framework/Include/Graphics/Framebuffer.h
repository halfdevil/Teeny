#pragma once

#include "Core/StdHeaders.h"
#include "Graphics/Texture.h"

class Framebuffer
{
public:

  Framebuffer() = default;
  ~Framebuffer()
  {
    destroy();
  }

  GLuint getHandle() const 
  {
    return mHandle;
  }

  uint32_t getWidth() const
  {
    return mWidth;
  }

  uint32_t getHeight() const
  {
    return mHeight;
  }

  const Texture& getColorTexture(uint32_t index) const
  {
    return *mColorTextures[index].get();
  }

  const Texture& getDepthTexture() const
  {
    return *mDepthTexture.get();
  }

  void create(uint32_t width, uint32_t height, GLenum depthFormat);
  void destroy();

  void addColorTexture(GLenum colorFormat);
  void activate();
  void deactivate();

private:

  GLuint mHandle{ 0 };
  uint32_t mWidth{ 0 };
  uint32_t mHeight{ 0 };
  std::vector<std::unique_ptr<Texture>> mColorTextures;
  std::unique_ptr<Texture> mDepthTexture{ nullptr };
};
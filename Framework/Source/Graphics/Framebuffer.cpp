#include "Graphics/Framebuffer.h"
#include "Core/Core.h"

void Framebuffer::create(uint32_t width, uint32_t height, GLenum depthFormat)
{
  glCreateFramebuffers(1, &mHandle);
  if (!mHandle)
  {
    EXIT("glCreateFramebuffers() failed");
  }

  if (depthFormat)
  {
    mDepthTexture = std::make_unique<Texture>(GL_TEXTURE_2D);
    mDepthTexture->create(width, height, depthFormat);

    const GLfloat border[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    glTextureParameterfv(mDepthTexture->getHandle(), GL_TEXTURE_BORDER_COLOR, border);

    TextureProperties properties = mDepthTexture->getProperties();
    properties.addressS = GL_CLAMP_TO_BORDER;
    properties.addressT = GL_CLAMP_TO_BORDER;
    mDepthTexture->setProperties(properties);

    glNamedFramebufferTexture(mHandle, GL_DEPTH_ATTACHMENT, mDepthTexture->getHandle(), 0);
  }

  const GLenum status = glCheckNamedFramebufferStatus(mHandle, GL_FRAMEBUFFER);
  ASSERT(status == GL_FRAMEBUFFER_COMPLETE, "glCheckNamedFramebufferStatus() failed");
}

void Framebuffer::destroy()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  if (mHandle)
  {
    glDeleteFramebuffers(1, &mHandle);
  }
}

void Framebuffer::addColorTexture(GLenum colorFormat)
{
  if (colorFormat)
  {
    auto colorTexture = std::make_unique<Texture>(GL_TEXTURE_2D);
    colorTexture->create(mWidth, mHeight, colorFormat);

    TextureProperties properties = mDepthTexture->getProperties();
    properties.addressS = GL_CLAMP_TO_EDGE;
    properties.addressT = GL_CLAMP_TO_EDGE;
    mDepthTexture->setProperties(properties);

		glNamedFramebufferTexture(mHandle, GL_COLOR_ATTACHMENT0 + (uint32_t)mColorTextures.size(), 
      colorTexture->getHandle(), 0);

    const GLenum status = glCheckNamedFramebufferStatus(mHandle, GL_FRAMEBUFFER);
    ASSERT(status == GL_FRAMEBUFFER_COMPLETE, "glCheckNamedFramebufferStatus() failed");
    
    mColorTextures.push_back(std::move(colorTexture));
  }
}

void Framebuffer::activate()
{
  glBindFramebuffer(GL_FRAMEBUFFER, mHandle);
  glViewport(0, 0, mWidth, mHeight);
}

void Framebuffer::deactivate()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
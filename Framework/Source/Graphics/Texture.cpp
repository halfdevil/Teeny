#include "Graphics/Texture.h"
#include "Core/Core.h"
#include "FS/FS.h"
#include <stb_image.h>

uint32_t getNumMipMapLevels(uint32_t width, uint32_t height)
{
  uint32_t levels{ 1 };

  while ((width | height) << levels)
    levels++;

  return levels;
}

void Texture::setProperties(const TextureProperties& properties)
{
  mProperties = properties;
  glTextureParameteri(mHandle, GL_TEXTURE_MIN_FILTER, properties.minFilter);
	glTextureParameteri(mHandle, GL_TEXTURE_MAG_FILTER, properties.magFilter);
  glTextureParameteri(mHandle, GL_TEXTURE_WRAP_R, properties.addressR);
  glTextureParameteri(mHandle, GL_TEXTURE_WRAP_S, properties.addressS);
  glTextureParameteri(mHandle, GL_TEXTURE_WRAP_T, properties.addressT);
  glTextureParameteri(mHandle, GL_TEXTURE_MAX_ANISOTROPY , properties.anisotripicFilter);
}

void Texture::create(const std::string& fileName)
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glCreateTextures(mType, 1, &mHandle);

  if (!mHandle)
  {
    EXIT("glCreateTextures() failed");
  }
  glTextureParameteri(mHandle, GL_TEXTURE_MAX_LEVEL, 0);

  if (mType == GL_TEXTURE_2D)
  {
    PhysicalFile file;
    file.open(fileName, FileOpenMode::OpenRead);
  
    FileReader reader(file);
    auto buffer = std::make_unique<uint8_t[]>(reader.getSize());
    reader.read(&buffer[0], reader.getSize());

    int32_t width{ 0 };
    int32_t height{ 0 };

    auto* image = stbi_load_from_memory(&buffer[0], reader.getSize(), &width, &height, 
      nullptr, STBI_rgb_alpha);

    if (!image)
    {
      EXIT("stbi_load_from_memory() failed for: %s", fileName.c_str());
    }

    uint32_t numMipMaps = getNumMipMapLevels(width, height);

    glTextureStorage2D(mHandle, numMipMaps, GL_RGBA8, width, height);
    glTextureSubImage2D(mHandle, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

    stbi_image_free(image);

    glGenerateTextureMipmap(mHandle);
    glTextureParameteri(mHandle, GL_TEXTURE_MAX_LEVEL, numMipMaps - 1);

    setProperties({
      .minFilter = GL_LINEAR_MIPMAP_LINEAR,
      .magFilter = GL_LINEAR
    });
  }
}

void Texture::create(uint32_t width, uint32_t height, GLenum internalFormat)
{
  glCreateTextures(mType, 1, &mHandle);
  if (!mHandle)
  {
    EXIT("glCreateTextures() failed");
  }

  glTextureParameteri(mHandle, GL_TEXTURE_MAX_LEVEL, 0);
	glTextureStorage2D(mHandle, getNumMipMapLevels(width, height), internalFormat, width, height);

  setProperties({
    .minFilter = GL_LINEAR,
    .magFilter = GL_LINEAR
  });
}

void Texture::destroy()
{
  if (mHandle)
  {
    glDeleteTextures(1, &mHandle);
  }
}
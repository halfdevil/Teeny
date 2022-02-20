#pragma once

#include "Core/StdHeaders.h"
#include <glad/glad.h>

struct TextureProperties
{
	GLenum minFilter{ GL_LINEAR_MIPMAP_LINEAR };
	GLenum magFilter{ GL_LINEAR_MIPMAP_LINEAR };
	GLenum addressR{ GL_CLAMP_TO_EDGE };
	GLenum addressS{ GL_CLAMP_TO_EDGE };
	GLenum addressT{ GL_CLAMP_TO_EDGE };
	uint32_t anisotripicFilter{ 0 };
};

class Texture
{
public:

	Texture(GLenum type)
		: mType(type)
	{
	}

	~Texture()
	{
		destroy();
	}

	GLenum getType() const
	{
		return mType;
	}

	GLuint getHandle() const
	{
		return mHandle;
	}

	GLuint64 getHandleBindless() const
	{
		return mHandleBindless;
	}

	const TextureProperties& getProperties() const
	{
		return mProperties;
	}

	void setProperties(const TextureProperties& properties);
	void create(const std::string& fileName);
	void create(uint32_t width, uint32_t height, GLenum internalFormat);
	void destroy();

private:

	GLenum mType{ 0 };
	GLuint mHandle{ 0 };
	GLuint64 mHandleBindless{ 0 };
	TextureProperties mProperties;
};
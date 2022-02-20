#pragma once

#include "Core/StdHeaders.h"
#include <glad/glad.h>

class Shader
{
public:

	Shader(GLenum type)
		: mType(type)
	{
	}

	~Shader()
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

	void create(const std::string& fileName);
	void create(const std::string& source, const std::string& debugFileName);
	void destroy();

protected:

	std::string readFile(const std::string& fileName);
	void printSource(const std::string& source);

private:

	GLenum mType{ GL_VERTEX_SHADER };
	GLuint mHandle{ 0 };
};
#pragma once

#include "Graphics/Shader.h"

class Program
{
public:

	Program() = default;
	~Program()
	{
		destroy();
	}

	GLuint getHandle() const
	{
		return mHandle;
	}

	void create(std::vector<const Shader*> shaders);
	void destroy();
	void activate();

private:

	GLuint mHandle{ 0 };
};
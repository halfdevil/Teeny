#include "Graphics/Shader.h"
#include "Core/Core.h"
#include "FS/FS.h"

void Shader::create(const std::string& fileName)
{
	create(readFile(fileName), fileName);
}

void Shader::create(const std::string& source, const std::string& debugFileName)
{
	mHandle = glCreateShader(mType);
	if (!mHandle)
	{
		EXIT("glCreateShader() failed");
	}

	const GLchar* shaderSource = source.c_str();

	glShaderSource(mHandle, 1, &shaderSource, nullptr);
	glCompileShader(mHandle);

	GLint status{ GL_TRUE };
	glGetShaderiv(mHandle, GL_COMPILE_STATUS, &status);

	if (!status)
	{
		char buffer[8192];
		GLsizei length{ 0 };
		glGetShaderInfoLog(mHandle, sizeof(buffer), &length, buffer);

		if (length)
		{
#ifdef DEBUG_BUILD
			printSource(source);
#endif

			ASSERT(false, "%s (File: %s)", buffer, debugFileName.c_str());
		}
	}
}

void Shader::destroy()
{
	if (mHandle)
	{
		glDeleteShader(mHandle);
	}
}

std::string Shader::readFile(const std::string& fileName)
{
	PhysicalFile file;
	file.open(fileName, FileOpenMode::OpenRead);

	FileReader reader(file);
	auto buffer = std::make_unique<char[]>(reader.getSize() + 1);
	reader.read(&buffer[0], reader.getSize());
	buffer[reader.getSize()] = 0;

	std::string source(buffer.get());

	while (source.find("#include ") != source.npos)
	{
		const auto pos = source.find("#include ");
		const auto p1 = source.find('<', pos);
		const auto p2 = source.find('>', pos);

		if (p1 == source.npos || p2 == source.npos || p2 <= p1)
		{
			LOGERROR("Error loading shader: %s", fileName.c_str());
			return std::string();
		}

		const std::string name = source.substr(p1 + 1, p2 - p1 - 1);
		const std::string include = readFile(name);

		source.replace(pos, p2 - pos + 1, include.c_str());
	}

	return source;
}

void Shader::printSource(const std::string& source)
{
}
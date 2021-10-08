#include "Graphics/Program.h"
#include "Core/Core.h"

void Program::create(std::vector<const Shader*> shaders)
{
  mHandle = glCreateProgram();
  if (!mHandle)
  {
    EXIT("glCreateProgram() failed");
  }

  for (const auto& shader : shaders)
  {
    glAttachShader(mHandle, shader->getHandle());
  }

  glLinkProgram(mHandle);

  GLint status{ GL_TRUE };
  glGetProgramiv(mHandle, GL_LINK_STATUS, &status);

  if (!status)
  {
    char buffer[8192];
    GLsizei length{ 0 };
    glGetProgramInfoLog(mHandle, sizeof(buffer), &length, buffer);

    if (length)
    {
      ASSERT(false, "Program linking failed: %s", buffer);
    }
  }

#ifdef DEBUG_BUILD
  glValidateProgram(mHandle);
  glGetProgramiv(mHandle, GL_VALIDATE_STATUS, &status);

  if (!status)
  {
    char buffer[8192];
    GLsizei length{ 0 };
    glGetProgramInfoLog(mHandle, sizeof(buffer), &length, buffer);

    if (length)
    {
      LOGWARNING("Program validation failed: %s", buffer);
    }
  }
#endif
}

void Program::destroy()
{
  if (mHandle)
  {
    glDeleteProgram(mHandle);
  }
}

void Program::activate()
{
  glUseProgram(mHandle);
}
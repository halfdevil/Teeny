#include "Cube.h"
#include "Core/Core.h"
#include "Graphics/Graphics.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::mat4;
using glm::vec3;

static const char* vertexShaderSource = R"(
  #version 460 core
  layout(std140, binding = 0) uniform PerFrameData
  {
    uniform mat4 MVP;
    uniform int isWireframe;
  };

  layout (location = 0) out vec3 color;
  const vec3 pos[8] = vec3[8] 
  (
    vec3(-1.0,-1.0, 1.0),
    vec3( 1.0,-1.0, 1.0),
    vec3( 1.0, 1.0, 1.0),
    vec3(-1.0, 1.0, 1.0),

    vec3(-1.0,-1.0,-1.0),
    vec3( 1.0,-1.0,-1.0),
    vec3( 1.0, 1.0,-1.0),
    vec3(-1.0, 1.0,-1.0)
  );

  const vec3 col[8] = vec3[8] 
  (
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0),
    vec3(1.0, 1.0, 0.0),

    vec3(1.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0),
    vec3(0.0, 1.0, 0.0),
    vec3(1.0, 0.0, 0.0)
  );

  const int indices[36] = int[36]
  (
    0, 1, 2, 2, 3, 0,
    1, 5, 6, 6, 2, 1,
    7, 6, 5, 5, 4, 7,
    4, 0, 3, 3, 7, 4,
    4, 5, 1, 1, 0, 4,
    3, 2, 6, 6, 7, 3
  );

  void main() 
  {
    int idx = indices[gl_VertexID];
    gl_Position = MVP * vec4(pos[idx], 1.0);
    color = isWireframe > 0 ? vec3(0.0) : col[idx];
  }
)";

static const char* fragmentShaderSource = R"(
  #version 460 core
  layout (location = 0) in vec3 color;
  layout (location = 0) out vec4 fragColor;

  void main()
  {
    fragColor = vec4(color, 1.0);
  }
)";

struct PerFrameData
{
	mat4 mvp;
	int isWireframe;
};

void Cube::run()
{
  Graphics graphics;
  graphics.create();
  graphics.setClearColor(0.5f, 0.5f, 0.5f);

  Shader vertexShader(GL_VERTEX_SHADER);
  vertexShader.create(vertexShaderSource, "traingle.vert");

  Shader fragmentShader(GL_FRAGMENT_SHADER);
  fragmentShader.create(fragmentShaderSource, "triangle.frag");

  Program program;
  program.create({&vertexShader, &fragmentShader});

  VertexArray vertexArray;
  vertexArray.create();

  constexpr uint32_t bufferSize = sizeof(PerFrameData);

  Buffer perFrameDataBuffer(GL_UNIFORM_BUFFER);
  perFrameDataBuffer.create(bufferSize, nullptr, GL_DYNAMIC_STORAGE_BIT);
  perFrameDataBuffer.bindRange(0, 0, sizeof(PerFrameData));
  
  DepthStencilState depthStencilState;
  depthStencilState.depthTestEnable = true;
  graphics.setDepthStencilState(depthStencilState);

  RasterizationState rasterizerState;
  rasterizerState.polygonOffsetLineEnable = true;
  rasterizerState.polygonOffsetFactor = -1.0f;
  rasterizerState.polygonOffsetUnits = -1.0f;
  
  while (!mWindow.isClosed())
  {
    graphics.setViewport(0, 0, mWindow.getWidth(), mWindow.getHeight());
    graphics.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program.activate();
    vertexArray.activate();

    const mat4 m = glm::rotate(glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, -3.5f)), 
      (float)glfwGetTime(), vec3(1.0f, 1.0f, 1.0f));

    const float ratio = mWindow.getWidth() / (float)mWindow.getHeight();
    const mat4 p = glm::perspective(45.0f, ratio, 0.1f, 1000.0f);

    PerFrameData perFrameData =
    {
      .mvp = p * m,
      .isWireframe = false
    };   

    perFrameDataBuffer.upload(0, bufferSize, &perFrameData);

    rasterizerState.polygonMode = GL_FILL;
    graphics.setRasterizationState(rasterizerState);
    vertexArray.draw(GL_TRIANGLES, 0, 36);

    perFrameData.isWireframe = true;
    perFrameDataBuffer.upload(0, bufferSize, &perFrameData);

    rasterizerState.polygonMode = GL_LINE;
    graphics.setRasterizationState(rasterizerState);
    vertexArray.draw(GL_TRIANGLES, 0, 36);

    mWindow.present();
    mWindow.pollEvents();
  }
}

int main(int argc, char* argv[])
{
  Cube app;
  app.create("Teeny - Cube", 1024, 768);
  app.run();

  return 0;
}
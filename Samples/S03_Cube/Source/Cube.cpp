#include "Cube.h"
#include "Core/Core.h"
#include "Graphics/Graphics.h"
#include "Scene/Scene.h"
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

Cube::Cube()
  : mPerFrameDataBuffer(GL_UNIFORM_BUFFER)
{  
}

void Cube::init()
{
  mInput.addAction({
    .name = "exit",
    .keys{ GLFW_KEY_ESCAPE }
  });

  mInput.bindAction("exit", InputEvent::Pressed, [this](int32_t key) {
    exit();
  });

  Shader vertexShader(GL_VERTEX_SHADER);
  vertexShader.create(vertexShaderSource, "traingle.vert");

  Shader fragmentShader(GL_FRAGMENT_SHADER);
  fragmentShader.create(fragmentShaderSource, "triangle.frag");

  mProgram.create({&vertexShader, &fragmentShader});
  mVertexArray.create();

  mPerFrameDataBuffer.create(sizeof(PerFrameData), nullptr, GL_DYNAMIC_STORAGE_BIT);
  mPerFrameDataBuffer.bindRange(0, 0, sizeof(PerFrameData));
  
  mGraphics.setDepthStencilState({
    .depthTestEnable = true
  });

  mRasterizationState =
  {
    .polygonOffsetLineEnable = true,
    .polygonOffsetFactor = -1.0f,
    .polygonOffsetUnits = -1.0f
  };
  
  mGraphics.setRasterizationState(mRasterizationState);
}

void Cube::appLoop()
{
  mGraphics.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  mProgram.activate();
  mVertexArray.activate();

  const mat4 m = glm::rotate(glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, -3.5f)), 
    (float)glfwGetTime(), vec3(1.0f, 1.0f, 1.0f));

  const float ratio = mWindow.getWidth() / (float)mWindow.getHeight();
  const mat4 p = glm::perspective(45.0f, ratio, 0.1f, 1000.0f);

  PerFrameData perFrameData =
  {
    .mvp = p * m,
    .isWireframe = false
  };   

  mPerFrameDataBuffer.upload(0, sizeof(PerFrameData), &perFrameData);
  mRasterizationState.polygonMode = GL_FILL;
  mGraphics.setRasterizationState(mRasterizationState);
  mVertexArray.draw(GL_TRIANGLES, 0, 36);

  perFrameData.isWireframe = true;
  mPerFrameDataBuffer.upload(0, sizeof(PerFrameData), &perFrameData);

  mRasterizationState.polygonMode = GL_LINE;
  mGraphics.setRasterizationState(mRasterizationState);
  mVertexArray.draw(GL_TRIANGLES, 0, 36);
}

int main(int argc, char* argv[])
{
  Cube app;
  app.create("Teeny - Cube", 1024, 768);
  app.run();

  return 0;
}
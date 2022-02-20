#include "Triangle.h"
#include "Core/Core.h"
#include "Graphics/Graphics.h"

static const char* vertexShaderSource = R"(
  #version 460 core
  layout (location = 0) out vec3 color;
  const vec2 pos[3] = vec2[3] 
  (
    vec2(-0.6, -0.4),
    vec2( 0.6, -0.4),
    vec2( 0.0,  0.6)
  );

  const vec3 col[3] = vec3[3] 
  (
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0)
  );

  void main() 
  {
    gl_Position = vec4(pos[gl_VertexID], 0.0, 1.0);
    color = col[gl_VertexID];
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

void Triangle::init()
{
	Shader vertexShader(GL_VERTEX_SHADER);
	vertexShader.create(vertexShaderSource, "traingle.vert");

	Shader fragmentShader(GL_FRAGMENT_SHADER);
	fragmentShader.create(fragmentShaderSource, "triangle.frag");

	mProgram.create({ &vertexShader, &fragmentShader });
	mVertexArray.create();
}

void Triangle::appLoop()
{
	mGraphics.clear(GL_COLOR_BUFFER_BIT);
	mProgram.activate();
	mVertexArray.activate();
	mVertexArray.draw(GL_TRIANGLES, 0, 3);
}

int main(int argc, char* argv[])
{
	Triangle app;
	app.create("Teeny - Triangle", 1280, 720);
	app.run();

	return 0;
}
#include "Core/Window.h"
#include "Core/Core.h"

void Window::create(const std::string& title, uint32_t width, uint32_t height)
{
  glfwSetErrorCallback([](int error, const char* description) {
    LOGERROR("Error: %s", description);
  });

  if (!glfwInit())
  {
    EXIT("glfwInit() failed");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

  const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

  mWidth = (width == 0) ? videoMode->width : width;
  mHeight = (height == 0) ? videoMode->height : height;

  mHandle = glfwCreateWindow(mWidth, mHeight, title.c_str(), nullptr, nullptr);
  if (!mHandle)
  {
    glfwTerminate();
    EXIT("glfwCreateWindow() failed");
  }

  glfwSetWindowUserPointer(mHandle, this);
  glfwMakeContextCurrent(mHandle);
  glfwSwapInterval(0);
  
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    EXIT("gladLoadGLLoader() failed");
  }

  glfwSetKeyCallback(mHandle, [](GLFWwindow* handle, int key, int scancode, int action, int mods) {
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(handle));
    if (window)
    {
      window->onKeyCallback.notify(key, action == GLFW_PRESS);
    }
  });
}

void Window::destroy()
{
  glfwDestroyWindow(mHandle);
  glfwTerminate();
}

bool Window::isClosed() const
{
  return glfwWindowShouldClose(mHandle);
}

void Window::close()
{
  glfwSetWindowShouldClose(mHandle, GLFW_TRUE);
}

void Window::pollEvents()
{
  glfwPollEvents();
}

void Window::present()
{
  glfwSwapBuffers(mHandle);
}
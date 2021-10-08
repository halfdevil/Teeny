#include "Core/Application.h"
#include "Core/Core.h"

void Application::create(const std::string& title, uint32_t width, uint32_t height)
{
  mWindow.create(title, width, height);
}

void Application::destroy()
{  
}
#pragma once

#include "Core/StdHeaders.h"
#include "Core/Logger.h"
#include "Core/Debugger.h"
#include "Core/Window.h"

class Application
{
public:

  Application() = default;
  virtual ~Application()
  {
    destroy();
  }

  const Window& getWindow() const 
  {
    return mWindow;
  }

  void create(const std::string& title, uint32_t width = 0, uint32_t height = 0);
  void destroy();

protected:

  Logger mLogger;
  Debugger mDebugger;
  Window mWindow;
};
#pragma once

#include "Core/StdHeaders.h"
#include "Core/Logger.h"
#include "Core/Debugger.h"
#include "Core/Window.h"
#include "Core/Timer.h"
#include "Graphics/Graphics.h"
#include "Input/Input.h"

class Application
{
public:

  Application() = default;
  virtual ~Application()
  {
    destroy();
  }

  void create(const std::string& title, uint32_t width = 0, uint32_t height = 0);
  void destroy();
  void exit();
  void run();

protected:

  virtual void init();
  virtual void appLoop();

protected:

  Logger mLogger;
  Debugger mDebugger;
  Window mWindow;
  Timer mTimer;
  Graphics mGraphics;
  Input mInput;
};
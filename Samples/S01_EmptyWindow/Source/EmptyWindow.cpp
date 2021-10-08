#include "EmptyWindow.h"
#include "Core/Core.h"
#include "Graphics/Graphics.h"

void EmptyWindow::run()
{
  Graphics graphics;
  graphics.create();
  graphics.setClearColor(0.5f, 0.5f, 0.5f);

  while (!mWindow.isClosed())
  {
    graphics.clear(GL_COLOR_BUFFER_BIT);

    mWindow.present();
    mWindow.pollEvents();
  }
}

int main(int argc, char* argv[])
{
  EmptyWindow app;
  app.create("Teeny - Empty Window", 1280, 720);
  app.run();

  return 0;
}
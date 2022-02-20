#include "Core/Application.h"
#include "Core/Core.h"

void Application::create(const std::string& title, uint32_t width, uint32_t height)
{
	mWindow.create(title, width, height);
	mGraphics.create();
	mGraphics.setViewport(0, 0, mWindow.getWidth(), mWindow.getHeight());
	mInput.create(mWindow);
}

void Application::destroy()
{
}

void Application::exit()
{
	mWindow.close();
}

void Application::run()
{
	init();
	mTimer.start();

	while (!mWindow.isClosed())
	{
		appLoop();

		mWindow.present();
		mWindow.pollEvents();
		mTimer.update();
		mInput.update();
	}
}

void Application::init()
{
}

void Application::appLoop()
{
}
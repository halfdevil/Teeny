#pragma once

#include "Core/StdHeaders.h"
#include "Core/Observer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:

	Window() = default;
	~Window()
	{
		destroy();
	}

	GLFWwindow* getHandle() const
	{
		return mHandle;
	}

	uint32_t getWidth() const
	{
		return mWidth;
	}

	uint32_t getHeight() const
	{
		return mHeight;
	}

	void create(const std::string& title, uint32_t width = 0, uint32_t height = 0);
	void destroy();

	bool isClosed() const;
	void close();
	void pollEvents();
	void present();

public:

	Observer<int32_t, bool> onKeyCallback;

private:

	GLFWwindow* mHandle{ nullptr };
	uint32_t mWidth{ 0 };
	uint32_t mHeight{ 0 };
};
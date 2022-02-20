#include "EmptyWindow.h"
#include "Core/Core.h"
#include "Graphics/Graphics.h"

void EmptyWindow::appLoop()
{
	mGraphics.clear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char* argv[])
{
	EmptyWindow app;
	app.create("Teeny - Empty Window", 1280, 720);
	app.run();

	return 0;
}
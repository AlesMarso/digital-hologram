#include <iostream>
#include <gui/Window.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	try
	{
		gui::Window window;

		if (!window.Init(hInstance))
			return -1;

		if (!window.Create("Hologram"))
			return -1;

		int res = window.Run();
	}
	catch (std::exception ex)
	{

	}

	return 0;
}

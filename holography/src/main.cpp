#include <iostream>
#include <gui/Window.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	MSG msg;

	try
	{
		gui::Window window;

		if (!window.Init(hInstance))
			return -1;

		if (!window.Create("Hologram"))
			return -1;

		while (GetMessage(&msg, nullptr, 0, 0) > 0)
		{
			if (msg.message == WM_QUIT)
				return static_cast<int>(msg.wParam);

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	catch (std::exception ex)
	{

	}

	return static_cast<int>(msg.wParam);
}

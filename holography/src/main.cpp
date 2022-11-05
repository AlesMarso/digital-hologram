#include <iostream>
#include <gui/Window.h>
#include <gdiplus.h>
#include "math/FFT.h"

int main()
{
	std::vector<math::Complex> input;
	for (int i = 0; i < 8; i++)
		input.push_back(math::Complex{static_cast<float>(i), static_cast<float>(i)});

	input = math::fft(input);

	try
	{
		gui::Window window;

		if (!window.Init(GetModuleHandle(nullptr)))
			throw std::exception("Failde window initialization");

		std::cout << "Window initialization is complite" << std::endl;

		if (!window.Create("Hologram"))
			throw std::exception("Failde window createion");

		std::cout << "Window creation is complite" << std::endl;

		int res = window.Run();

		std::cout << "Window stop with code = " << res << std::endl;
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return 0;
}

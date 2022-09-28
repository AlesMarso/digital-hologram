#include <iostream>
#include <gui/Window.h>

#include <vulkan/vulkan.h>

int main()
{
	VkInstanceCreateInfo instacneInfo = {};
	VkInstance instancevk;

	if (vkCreateInstance(&instacneInfo, nullptr, &instancevk) == VK_SUCCESS)
		std::cout << "Vulkan is initialized" << std::endl;

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

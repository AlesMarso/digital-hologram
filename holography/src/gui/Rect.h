#pragma once

#include <windows.h>
#include <cstdint>

namespace gui
{
	class Rect
	{
	public:
		Rect();
		Rect(HWND);
		~Rect();

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

		uint32_t GetX() const;
		uint32_t GetY() const;

	private:
		RECT m_Rect;
	};
}

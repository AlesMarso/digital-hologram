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

		uint32_t GetClientWidth() const;
		uint32_t GetClientHeight() const;

		uint32_t GetClientX() const;
		uint32_t GetClientY() const;

	protected:
		RECT m_Rect;
		RECT m_ClientRect;
	};
}

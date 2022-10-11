#pragma once

#include <cstdint>

namespace gui
{
	class Color
	{
	public:
		Color() = default;
		Color(uint8_t red, uint8_t green, uint8_t blue);
		Color(float red, float green, float blue);
		Color(uint32_t color);
		~Color() = default;

		uint8_t bRed() const;
		uint8_t bGreen() const;
		uint8_t bBlue() const;

		float fRed() const;
		float fGreen() const;
		float fBlue() const;

		void operator=(uint32_t);

	private:
		uint8_t m_Red;
		uint8_t m_Green;
		uint8_t m_Blue;

		const uint8_t m_bMaxColorVal = 255;
	};
}

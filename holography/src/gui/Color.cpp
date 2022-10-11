#include "Color.h"

gui::Color::Color(uint8_t red, uint8_t green, uint8_t blue)
{
	m_Red = red;
	m_Green = green;
	m_Blue = blue;
}

gui::Color::Color(float red, float green, float blue)
{
	m_Red = static_cast<uint8_t>(red * m_bMaxColorVal);
	m_Green = static_cast<uint8_t>(green * m_bMaxColorVal);
	m_Blue = static_cast<uint8_t>(blue * m_bMaxColorVal);
}

gui::Color::Color(uint32_t color)
{
	m_Red = ((color & 0xff0000) >> 16);
	m_Green = ((color & 0x00ff00) >> 8);
	m_Blue = (color & 0x0000ff);
}

uint8_t gui::Color::bRed() const
{
	return m_Red;
}

uint8_t gui::Color::bGreen() const
{
	return m_Green;
}

uint8_t gui::Color::bBlue() const
{
	return m_Blue;
}

float gui::Color::fRed() const
{
	return (float)m_Red / (float)m_bMaxColorVal;
}

float gui::Color::fGreen() const
{
	return (float)m_Green / (float)m_bMaxColorVal;
}

float gui::Color::fBlue() const
{
	return (float)m_Blue / (float)m_bMaxColorVal;
}

void gui::Color::operator=(uint32_t color)
{
	m_Red = ((color & 0xff0000) >> 16);
	m_Green = ((color & 0x00ff00) >> 8);
	m_Blue = (color & 0x0000ff);
}

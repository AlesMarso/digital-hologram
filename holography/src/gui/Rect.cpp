#include "Rect.h"

gui::Rect::Rect()
	: m_Rect()
{
}

gui::Rect::Rect(HWND hwnd)
{
	GetClientRect(hwnd, &m_Rect);
}

gui::Rect::~Rect()
{
}

uint32_t gui::Rect::GetWidth() const
{
	return m_Rect.right - m_Rect.left;
}

uint32_t gui::Rect::GetHeight() const
{
	return m_Rect.bottom - m_Rect.top;
}

uint32_t gui::Rect::GetX() const
{
	return m_Rect.left;
}

uint32_t gui::Rect::GetY() const
{
	return m_Rect.top;
}

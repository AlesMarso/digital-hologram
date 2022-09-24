#include "Rect.h"

gui::Rect::Rect()
	: m_Rect()
{
}

gui::Rect::Rect(HWND hwnd)
{
	GetClientRect(hwnd, &m_ClientRect);
	GetWindowRect(hwnd, &m_Rect);
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

uint32_t gui::Rect::GetClientWidth() const
{
	return m_ClientRect.right - m_ClientRect.left;
}

uint32_t gui::Rect::GetClientHeight() const
{
	return m_ClientRect.bottom - m_ClientRect.top;
}

uint32_t gui::Rect::GetClientX() const
{
	return m_ClientRect.left;
}

uint32_t gui::Rect::GetClientY() const
{
	return m_ClientRect.top;
}

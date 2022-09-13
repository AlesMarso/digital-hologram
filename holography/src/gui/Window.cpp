#include "Window.h"

gui::Window::Window()
	: m_Width(DEF_WINDOW_WIDTH), m_Height(DEF_WINDOW_HEIGHT), m_hWnd(nullptr), m_hInstance(nullptr)
{
}

gui::Window::~Window()
{
}

bool gui::Window::Init(HINSTANCE hInst)
{
	WNDCLASSEXA wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));

	m_hInstance = hInst;

	wndClass.cbSize = sizeof(WNDCLASSEXA);
	wndClass.hInstance = hInst;
	wndClass.lpfnWndProc = MessageHandlerSetup;
	wndClass.lpszClassName = "HologramWindowClass";
	wndClass.lpszMenuName = MAKEINTRESOURCEA(IDR_MAIN_MENU);

	return RegisterClassExA(&wndClass);
}

bool gui::Window::Create(const char* title, uint32_t width, uint32_t height)
{
	m_hWnd = CreateWindowA(
		"HologramWindowClass",
		title,
		WS_CAPTION | WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		nullptr,
		nullptr,
		m_hInstance,
		this);

	if (!m_hWnd)
		return false;

	m_Width = width;
	m_Height = height;

	return true;
}

LRESULT gui::Window::OnCreate(const EventArgs&)
{
	return LRESULT();
}

LRESULT gui::Window::OnPaint(const EventArgs&)
{
	return LRESULT();
}

LRESULT gui::Window::OnSize(const EventArgs&)
{
	return LRESULT();
}

LRESULT gui::Window::OnDestroy(const EventArgs&)
{
	return LRESULT();
}

LRESULT gui::Window::OnClose(const EventArgs&)
{
	PostQuitMessage(0);
	return true;
}

LRESULT gui::Window::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	EventArgs args = { hWnd, wParam, lParam };

	switch (msg)
	{
	case WM_CREATE:
		return OnCreate(args);

	case WM_PAINT:
		return OnPaint(args);

	case WM_SIZE:
		return OnSize(args);

	case WM_DESTROY:
		return OnDestroy(args);

	case WM_CLOSE:
		return OnClose(args);

	default:
		break;
	}

	return DefWindowProcA(hWnd, msg, wParam, lParam);
}

LRESULT gui::Window::MessageHandlerSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);

		Window* pWnd = static_cast<Window*>(pCreate->lpCreateParams);

		SetWindowLongPtrA(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtrA(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::MessageHandlerThunk));
	}

	return DefWindowProcA(hWnd, msg, wParam, lParam);
}

LRESULT gui::Window::MessageHandlerThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	if(pWnd)
		return pWnd->MessageHandler(hWnd, msg, wParam, lParam);

	return DefWindowProcA(hWnd, msg, wParam, lParam);
}
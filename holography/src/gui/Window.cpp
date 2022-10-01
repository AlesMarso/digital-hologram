#include "Window.h"

gui::Window::Window()
	: m_hWnd(nullptr),
	m_hInstance(nullptr),
	m_OGLRenderContext(nullptr),
	m_RenderContext(new rctx::OpenGLRender())
{
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, nullptr);
}

gui::Window::~Window()
{
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
}

bool gui::Window::Init(HINSTANCE hInst)
{
	WNDCLASSEXA wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));

	wndClass.cbSize = sizeof(WNDCLASSEXA);
	wndClass.hInstance = hInst;
	wndClass.lpfnWndProc = MessageHandlerSetup;
	wndClass.lpszClassName = "HologramWindowClass";
	wndClass.lpszMenuName = MAKEINTRESOURCEA(IDR_MAIN_MENU);

	bool res = RegisterClassExA(&wndClass);

	if (res)
		InitializeComponents();

	return res;
}

bool gui::Window::Create(const char* title, uint32_t width, uint32_t height)
{
	m_hWnd = CreateWindowA("HologramWindowClass", title, WS_CAPTION | WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, m_hInstance, this);

	return m_hWnd != nullptr;
}

int gui::Window::Run()
{
	MSG msg = { 0 };

	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		if (msg.message == WM_QUIT)
			break;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}

LRESULT gui::Window::OnCreate(const EventArgs& args)
{
	OnInit(args);

	return m_RenderContext->Init(args.hWnd);
}

LRESULT gui::Window::OnPaint(const EventArgs& args)
{
	m_RenderContext->Draw(args.hWnd);

	return true;
}

LRESULT gui::Window::OnSize(const EventArgs& args)
{
	m_RenderContext->Resize(args.hWnd);
	m_RenderContext->Update();

	return true;
}

LRESULT gui::Window::OnDestroy(const EventArgs& args)
{
	return LRESULT();
}

LRESULT gui::Window::OnClose(const EventArgs& args)
{
	m_RenderContext->Close();
	PostQuitMessage(0);

	return true;
}

LRESULT gui::Window::OnSizing(const EventArgs& args)
{
	m_RenderContext->Resize(args.hWnd);
	m_RenderContext->Update();

	return true;
}

LRESULT gui::Window::OnInit(const EventArgs& args)
{
	share::HoloIniFileController holoIniFile;

	std::cout << "Load file = " << holoIniFile.GetImageName() << std::endl;

	return LRESULT();
}

void gui::Window::SetEvent(uint32_t event_id, uint32_t action_id, Event func)
{
	m_Events.SetEvent(event_id, action_id, func);
}

LRESULT gui::Window::OnFileExitMainMenu(const EventArgs& args)
{
	return OnClose(args);
}

LRESULT gui::Window::OnHelpAboutMainMenu(const EventArgs& args)
{
	MessageBoxA(args.hWnd, "About", "About", MB_OK);

	return true;
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

void gui::Window::InitializeComponents()
{
	SetEvent(ID_FILE_EXIT, ID_ACTION_MAIN_MENU, BIND_EVENT(gui::Window::OnFileExitMainMenu));
	SetEvent(ID_HELP_ABOUT, ID_ACTION_MAIN_MENU, BIND_EVENT(gui::Window::OnHelpAboutMainMenu));

	string1024 filename = { 0 };
	GetModuleFileName(nullptr, filename, 1024);

	m_CurrentDirectory = std::filesystem::path(filename).parent_path();

	std::cout << "Detected current executable directory = " << m_CurrentDirectory << std::endl;
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

	case WM_SIZING:
		return OnSizing(args);

	case WM_DESTROY:
		return OnDestroy(args);

	case WM_CLOSE:
		return OnClose(args);

	case WM_COMMAND:
		return m_Events(CONTROL_ID, ACTION_ID, args);

	default:
		break;
	}

	return DefWindowProcA(hWnd, msg, wParam, lParam);
}

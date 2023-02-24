#include "OpenGLRender.h"

rctx::OpenGLRender::OpenGLRender()
	: m_hWnd(nullptr),
	m_hDC(nullptr),
	m_hGLRC(nullptr),
	m_RenderScene(new rctx::OpenGLTestScene())
{
	m_InfoItems.push_back(OpenGLInfoItem(GL_VERSION, String));
	m_InfoItems.push_back(OpenGLInfoItem(GL_VENDOR, String));
	m_InfoItems.push_back(OpenGLInfoItem(GL_RENDERER, String));
	m_InfoItems.push_back(OpenGLInfoItem(GL_SHADING_LANGUAGE_VERSION, String));
}

rctx::OpenGLRender::OpenGLRender(HWND hwnd)
	: m_hWnd(hwnd),
	m_hDC(nullptr),
	m_hGLRC(nullptr),
	m_RenderScene(new rctx::OpenGLTestScene())
{
}

rctx::OpenGLRender::~OpenGLRender()
{
}

bool rctx::OpenGLRender::Init(HWND hWnd)
{
	PIXELFORMATDESCRIPTOR ppx;

	ZeroMemory(&ppx, sizeof(PIXELFORMATDESCRIPTOR));

	ppx.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	ppx.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	ppx.cColorBits = 32;
	ppx.cDepthBits = 32;
	ppx.nVersion = 1;
	ppx.iPixelType = PFD_TYPE_RGBA;

	m_hWnd = hWnd;
	HDC dc = GetWindowDC(hWnd);

	int iPixelFormat = ChoosePixelFormat(dc, &ppx);

	if (!iPixelFormat)
		return false;

	if (!SetPixelFormat(dc, iPixelFormat, &ppx))
		return false;

	m_hGLRC = wglCreateContext(dc);

	if (!m_hGLRC)
		return false;

	wglMakeCurrent(dc, m_hGLRC);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Is not init" << std::endl;
		return false;
	}

	std::cout << "GLEW is init" << std::endl;

	gui::Color lightGray = 0xd3d3d3;
	
	glClearColor(lightGray.fRed(), lightGray.fGreen(), lightGray.fBlue(), 1.0f);
	glClearDepth(1.0f);

	return true;
}

bool rctx::OpenGLRender::Load(HWND)
{
	m_RenderScene = new rctx::OpenGLDoubleFFT128x128points();

	std::for_each(m_InfoItems.begin(), m_InfoItems.end(), [](OpenGLInfoItem& item)
		{
			switch (item.m_Type)
			{
			case Int:
			{
				GLint info = -1;
				glGetIntegerv(item.m_Param, &info);

				std::cout << info << std::endl;
				break;
			}

			case String:
				std::cout << glGetString(item.m_Param) << std::endl;
				break;
			}
		});

	return m_RenderScene->Load();
}

void rctx::OpenGLRender::Render(HWND hWnd)
{
	PAINTSTRUCT paint;

	BeginPaint(hWnd, &paint);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!m_RenderScene->Calculate())
		return;

	if (!m_RenderScene->Draw())
		return;

	SwapBuffers(paint.hdc);
	EndPaint(hWnd, &paint);
}

void rctx::OpenGLRender::Resize(HWND hwnd)
{
	gui::Rect rect(hwnd);

	glViewport(0, 0, rect.GetClientWidth(), rect.GetClientHeight());
}

void rctx::OpenGLRender::Close()
{
	wglMakeCurrent(m_hDC, nullptr);
}

void rctx::OpenGLRender::Update()
{
	Render(m_hWnd);
}

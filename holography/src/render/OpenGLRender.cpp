#include "OpenGLRender.h"

rctx::OpenGLRender::OpenGLRender()
	: m_hWnd(nullptr),
	m_hDC(nullptr),
	m_hGLRC(nullptr),
	m_IsTextureLoad(false),
	m_Texture(0)
{
}

rctx::OpenGLRender::OpenGLRender(HWND hwnd)
	: m_hWnd(hwnd),
	m_hDC(nullptr),
	m_hGLRC(nullptr),
	m_IsTextureLoad(false),
	m_Texture(0)
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

	gui::Color lightGray = 0xd3d3d3;
	
	glClearColor(lightGray.fRed(), lightGray.fGreen(), lightGray.fBlue(), 1.0f);
	glClearDepth(1.0f);

	return true;
}

void rctx::OpenGLRender::Draw(HWND hWnd)
{
	PAINTSTRUCT paint;

	BeginPaint(hWnd, &paint);

	gui::Color white(0xffffff);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(white.fRed(), white.fGreen(), white.fBlue());

	if (!m_IsTextureLoad)
	{
		share::HoloIniFileController holoIniFile;

		LoadTexture(holoIniFile.GetImageFileName());
		m_IsTextureLoad = true;
	}

	glBegin(GL_QUADS);
	{
		glVertex2f(-0.95f, -0.95f);
		glVertex2f(-0.95f, 0.95f);
		glVertex2f(0.95f, 0.95f);
		glVertex2f(0.95f, -0.95f);
	}
	glEnd();

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
	Draw(m_hWnd);
}

void rctx::OpenGLRender::LoadTexture(std::filesystem::path imgPath)
{
	std::cout << "Load file = " << imgPath << std::endl;

	Gdiplus::Bitmap* bmp = new Gdiplus::Bitmap(imgPath.generic_wstring().c_str(), FALSE);

	auto imgWidth = bmp->GetWidth();
	auto imgHeight = bmp->GetHeight();

	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	auto bitmapData = new Gdiplus::BitmapData;
	Gdiplus::Rect rect(0, 0, imgWidth, imgHeight);

	bmp->LockBits(&rect, Gdiplus::ImageLockModeRead, bmp->GetPixelFormat(), bitmapData);

	auto* pixels = static_cast<unsigned*>(bitmapData->Scan0);

	bmp->UnlockBits(bitmapData);

	glDisable(GL_TEXTURE_2D);

	return;
}

#include "OpenGLRender.h"

rctx::OpenGLRender::OpenGLRender()
	: m_hWnd(nullptr),
	m_hDC(nullptr),
	m_hGLRC(nullptr),
	m_IsTextureLoad(false)
{
	m_vertices[0] = -0.95f;
	m_vertices[1] = -0.95f;

	m_vertices[2] = -0.95f;
	m_vertices[3] = 0.95f;

	m_vertices[4] = 0.95f;
	m_vertices[5] = 0.95f;

	m_vertices[6] = 0.95f;
	m_vertices[7] = -0.95f;
}

rctx::OpenGLRender::OpenGLRender(HWND hwnd)
	: m_hWnd(hwnd),
	m_hDC(nullptr),
	m_hGLRC(nullptr),
	m_IsTextureLoad(false)
{
	m_vertices[0] = -0.95f;
	m_vertices[1] = -0.95f;

	m_vertices[2] = -0.95f;
	m_vertices[3] = 0.95f;

	m_vertices[4] = 0.95f;
	m_vertices[5] = 0.95f;

	m_vertices[6] = 0.95f;
	m_vertices[7] = -0.95f;
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

	gui::Color lightGray = 0xd3d3d3;
	
	glClearColor(lightGray.fRed(), lightGray.fGreen(), lightGray.fBlue(), 1.0f);
	glClearDepth(1.0f);

	return true;
}

bool rctx::OpenGLRender::Load(HWND)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return false;
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

		m_PSIFirstTexture.CreateFromImage(holoIniFile.GetPSIFirstImage());
		m_PSISecondTexture.CreateFromImage(holoIniFile.GetPSISecondImage());
		m_PSIThirdTexture.CreateFromImage(holoIniFile.GetPSIThirdImage());
		m_PSIFourthTexture.CreateFromImage(holoIniFile.GetPSIFourthImage());

		m_IsTextureLoad = true;
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_PSIFirstTexture.GetTextureID());

	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	// First PSI Image
	//glBegin(GL_QUADS);
	//{
	//	glTexCoord2d(0.0f, 0.0f);
	//	glVertex2f(-0.95f, -0.95f);
	//
	//	glTexCoord2d(0.0f, 1.0f);
	//	glVertex2f(-0.05f, -0.95f);
	//
	//	glTexCoord2d(1.0f, 1.0f);
	//	glVertex2f(-0.05f, -0.05f);
	//
	//	glTexCoord2d(1.0f, 0.0f);
	//	glVertex2f(-0.95f, -0.05f);
	//}
	//glEnd();
	//glBindTexture(GL_TEXTURE_2D, 0);
	//
	//// Second PSI Image
	//glBindTexture(GL_TEXTURE_2D, m_PSISecondTexture.GetTextureID());
	//glBegin(GL_QUADS);
	//{
	//	glTexCoord2d(1.0f, 1.0f);
	//	glVertex2f(0.05f, -0.95f);
	//
	//	glTexCoord2d(0.0f, 1.0f);
	//	glVertex2f(0.95f, -0.95f);
	//
	//	glTexCoord2d(0.0f, 0.0f);
	//	glVertex2f(0.95f, -0.05f);
	//
	//	glTexCoord2d(1.0f, 0.0f);
	//	glVertex2f(0.05f, -0.05f);
	//}
	//glEnd();
	//glBindTexture(GL_TEXTURE_2D, 0);
	//
	//// Third PSI Image
	//glBindTexture(GL_TEXTURE_2D, m_PSIThirdTexture.GetTextureID());
	//glBegin(GL_QUADS);
	//{
	//	glTexCoord2d(1.0f, 1.0f);
	//	glVertex2f(0.05f, 0.05f);
	//
	//	glTexCoord2d(0.0f, 1.0f);
	//	glVertex2f(0.95f, 0.05f);
	//
	//	glTexCoord2d(0.0f, 0.0f);
	//	glVertex2f(0.95f, 0.95f);
	//
	//	glTexCoord2d(1.0f, 0.0f);
	//	glVertex2f(0.05f, 0.95f);
	//}
	//glEnd();
	//glBindTexture(GL_TEXTURE_2D, 0);
	//
	//// Fourth PSI Image
	//glBindTexture(GL_TEXTURE_2D, m_PSIFourthTexture.GetTextureID());
	//glBegin(GL_QUADS);
	//{
	//	glTexCoord2d(1.0f, 1.0f);
	//	glVertex2f(-0.95f, 0.05f);
	//
	//	glTexCoord2d(0.0f, 1.0f);
	//	glVertex2f(-0.05f, 0.05f);
	//
	//	glTexCoord2d(0.0f, 0.0f);
	//	glVertex2f(-0.05f, 0.95f);
	//
	//	glTexCoord2d(1.0f, 0.0f);
	//	glVertex2f(-0.95f, 0.95f);
	//}
	//glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);

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

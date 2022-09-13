#pragma once

#include <windows.h>
#include <render/IRender.h>
#include <gl/GLU.h>
#include <gl/GL.h>

namespace rctx
{
	class OpenGLRender : public IRender
	{
	public:
		OpenGLRender();
		OpenGLRender(HWND);
		~OpenGLRender();

		virtual bool Init(HWND) override;
		virtual void Draw(HWND) override;
		virtual void Resize() override;
		virtual void Close() override;

	private:
		HWND m_hWnd;
		HDC  m_hDC;
		HGLRC m_hGLRC;
	};
}


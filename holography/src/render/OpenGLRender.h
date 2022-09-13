#pragma once

#include <windows.h>
#include <render/IRender.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <gui/Rect.h>

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
		virtual void Resize(HWND) override;
		virtual void Close() override;
		virtual void Update() override;

	private:
		HWND m_hWnd;
		HDC  m_hDC;
		HGLRC m_hGLRC;
	};
}


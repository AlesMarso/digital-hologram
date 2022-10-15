#pragma once

#include <windows.h>
#include <render/IRender.h>

#include <gl/glew.h>

#include <CL/cl.h>

#include <gui/Rect.h>
#include <gui/Color.h>
#include <filesystem>
#include <gdiplus.h>
#include <iostream>

#include <share/HoloIniFileController.h>
#include <render/opengl/OpenGLTexture.h>
#include <render/opengl/secnes/IOpenGLScene.h>
#include <render/opengl/secnes/OpenGLTestSecene.h>
#include <render/opengl/secnes/OpenGLPSIScene.h>

namespace rctx
{
	class OpenGLRender : public IRender
	{
	public:
		OpenGLRender();
		OpenGLRender(HWND);
		~OpenGLRender();

		virtual bool Init(HWND) override;
		virtual bool Load(HWND) override;
		virtual void Render(HWND) override;
		virtual void Resize(HWND) override;
		virtual void Close() override;
		virtual void Update() override;

	private:
		HWND m_hWnd;
		HDC  m_hDC;
		HGLRC m_hGLRC;
		IOpenGLScene* m_RenderScene;
	};
}


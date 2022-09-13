#pragma once

#include <windows.h>
#include <cstdint>
#include <share/const.h>
#include <render/OpenGLRender.h>
#include <gui/event/Functor.h>

#include "resource.h"

#define CONTROL_ID (LOWORD(wParam))
#define ACTION_ID (HIWORD(wParam))

namespace gui {

	/// <summary>
	/// Класс окна OS Windows
	/// </summary>
	class Window
	{
	public:
		Window();
		~Window();

		bool Init(HINSTANCE);
		bool Create(const char*, uint32_t width = DEF_WINDOW_WIDTH, uint32_t height = DEF_WINDOW_HEIGHT);
		void SetEvent(uint32_t, uint32_t, Event);

	public:
		LRESULT OnFileExitMainMenu(const EventArgs&);

	public:
		virtual LRESULT OnCreate(const EventArgs&);
		virtual LRESULT OnPaint(const EventArgs&);
		virtual LRESULT OnSize(const EventArgs&);
		virtual LRESULT OnDestroy(const EventArgs&);
		virtual LRESULT OnClose(const EventArgs&);
		virtual LRESULT OnSizing(const EventArgs&);

	protected:
		virtual LRESULT MessageHandler(HWND, UINT, WPARAM, LPARAM);

	private:
		static LRESULT MessageHandlerSetup(HWND, UINT, WPARAM, LPARAM);
		static LRESULT MessageHandlerThunk(HWND, UINT, WPARAM, LPARAM);
		virtual void InitializeComponents();

	private:
		uint32_t m_Width;
		uint32_t m_Height;
		HWND m_hWnd;
		HINSTANCE m_hInstance;
		HGLRC m_OGLRenderContext;

	private:
		rctx::IRender* m_RenderContext;
		Functor m_Events;
	};
}

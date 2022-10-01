#pragma once

#include <iostream>
#include <windows.h>
#include <cstdint>
#include <share/const.h>
#include <render/OpenGLRender.h>
#include <gui/event/Functor.h>
#include <gdiplus.h>
#include <filesystem>

#include <share/IniFileController.h>

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

		/// <summary>
		/// 
		/// </summary>
		/// <param name="hInst"></param>
		/// <returns></returns>
		bool Init(HINSTANCE hInst);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="title"></param>
		/// <param name="width"></param>
		/// <param name="height"></param>
		/// <returns></returns>
		bool Create(const char* title, uint32_t width = DEF_WINDOW_WIDTH, uint32_t height = DEF_WINDOW_HEIGHT);
		
		int Run();
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="event_id"></param>
		/// <param name="action_id"></param>
		/// <param name="func"></param>
		void SetEvent(uint32_t event_id, uint32_t action_id, Event func);

	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="args"></param>
		/// <returns></returns>
		LRESULT OnFileExitMainMenu(const EventArgs& args);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="args"></param>
		/// <returns></returns>
		LRESULT OnHelpAboutMainMenu(const EventArgs& args);

	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="args"></param>
		/// <returns></returns>
		virtual LRESULT OnCreate(const EventArgs& args);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="args"></param>
		/// <returns></returns>
		virtual LRESULT OnPaint(const EventArgs& args);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="args"></param>
		/// <returns></returns>
		virtual LRESULT OnSize(const EventArgs& args);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="args"></param>
		/// <returns></returns>
		virtual LRESULT OnDestroy(const EventArgs& args);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="args"></param>
		/// <returns></returns>
		virtual LRESULT OnClose(const EventArgs& args);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="args"></param>
		/// <returns></returns>
		virtual LRESULT OnSizing(const EventArgs& args);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="args"></param>
		/// <returns></returns>
		virtual LRESULT OnInit(const EventArgs& args);

	protected:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="hWnd"></param>
		/// <param name="msg"></param>
		/// <param name="wParam"></param>
		/// <param name="lParam"></param>
		/// <returns></returns>
		virtual LRESULT MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="hWnd"></param>
		/// <param name="msg"></param>
		/// <param name="wParam"></param>
		/// <param name="lParam"></param>
		/// <returns></returns>
		static LRESULT MessageHandlerSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="hWnd"></param>
		/// <param name="msg"></param>
		/// <param name="wParam"></param>
		/// <param name="lParam"></param>
		/// <returns></returns>
		static LRESULT MessageHandlerThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		
		/// <summary>
		/// 
		/// </summary>
		virtual void InitializeComponents();

	private:
		HWND m_hWnd;
		HINSTANCE m_hInstance;
		HGLRC m_OGLRenderContext;

	private:
		rctx::IRender* m_RenderContext;
		Functor m_Events;

	private:
		ULONG_PTR m_gdiplusToken;
		Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;

	private:
		std::filesystem::path m_CurrentDirectory;
	};
}

#pragma once

#include <Windows.h>

#include <functional>
#include <map>

#define BIND_EVENT(funcname) std::bind(&funcname, this, std::placeholders::_1)

namespace gui
{
	struct EventArgs
	{
		HWND hWnd;
		WPARAM wParam;
		LPARAM lParam;
	};

	using Event = std::function<bool(const EventArgs&)>;
	using Action = std::map<uint32_t, Event>;

	class Functor
	{
	public:
		Functor() = default;
		~Functor();

		void SetEvent(uint32_t, uint32_t, Event);

		bool operator()(uint32_t, uint32_t, const EventArgs&);

	private:
		std::map<uint32_t, Action> m_Container;
	};
}

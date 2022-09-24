#pragma once

namespace rctx
{
	class IRender
	{
	public:
		IRender() = default;
		virtual ~IRender() = default;

		virtual bool Init(HWND) = 0;
		virtual void Draw(HWND) = 0;
		virtual void Resize(HWND) = 0;
		virtual void Close() = 0;
		virtual void Update() = 0;
	};
}

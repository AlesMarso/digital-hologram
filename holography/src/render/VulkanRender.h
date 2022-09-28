#pragma once

#include <render/IRender.h>

namespace rctx
{
	class VulkanRender : public IRender
	{
	public:

		VulkanRender() = default;
		~VulkanRender() = default;

		virtual bool Init(HWND) = 0;
		virtual void Draw(HWND) = 0;
		virtual void Resize(HWND) = 0;
		virtual void Close() = 0;
		virtual void Update() = 0;
	};
}

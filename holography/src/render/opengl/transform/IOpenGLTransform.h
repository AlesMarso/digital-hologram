#pragma once

#include <filesystem>

namespace rctx
{
	class IOpenGLTransform
	{
	public:
		IOpenGLTransform() = default;
		~IOpenGLTransform() = default;

		virtual void Init(const std::filesystem::path&) = 0;
		virtual void Execute() = 0;
	};
}

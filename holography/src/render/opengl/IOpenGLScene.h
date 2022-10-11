#pragma once

namespace rctx
{
	class IOpenGLScene
	{
	public:
		IOpenGLScene() = default;
		~IOpenGLScene() = default;

		virtual bool Load() = 0;
		virtual bool Calculate() = 0;
		virtual bool Draw() = 0;
		virtual bool Close() = 0;
	};
}

#pragma once


namespace rctx
{
	class IOpenGLTransform
	{
	public:
		IOpenGLTransform() = default;
		~IOpenGLTransform() = default;

		virtual void Init() = 0;
		virtual void Execute() = 0;
	};
}

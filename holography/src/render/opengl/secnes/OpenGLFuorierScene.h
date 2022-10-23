#pragma once

#include <GL/glew.h>

#include <render/opengl/secnes/IOpenGLScene.h>
#include <render/opengl/OpenGLTexture.h>
#include <render/opengl/shaders/Shader.h>
#include <render/opengl/shaders/GPUProgram.h>

namespace rctx
{
	class OpenGLFuorierScene : public IOpenGLScene
	{
	public:

		OpenGLFuorierScene() = default;
		~OpenGLFuorierScene() = default;

		bool Load() override;
		bool Calculate() override;
		bool Draw() override;
		bool Close() override;

	private:
		OpenGLTexture m_TestTexture;

		GPUProgram m_ComputeProgram;
		GPUProgram m_RenderProgram;
	};
}

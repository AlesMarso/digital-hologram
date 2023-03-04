#pragma once

#include "IOpenGLTransform.h"
#include <render/opengl/shaders/Shader.h>
#include <render/opengl/shaders/GPUProgram.h>
#include <render/opengl/buffers/VertexBufferObjectClass.h>
#include <render/opengl/buffers/VertexArrayObject.h>

#include <iostream>
#include <vector>

namespace rctx
{
	class OpenGLExpTransform : public IOpenGLTransform
	{
	public:
		OpenGLExpTransform() = default;
		OpenGLExpTransform(const std::filesystem::path&, GLuint, GLuint);
		virtual ~OpenGLExpTransform() = default;

		virtual void Init(const std::filesystem::path&) override;
		virtual void Execute() override;

	private:
		GPUProgram m_ExpProgram;

		std::filesystem::path m_SrcPath;

		GLuint m_AmplitudeImage;
		GLuint m_PhaseImage;
	};
}

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
	class OpenGLFFTTransform : public IOpenGLTransform
	{
	public:
		OpenGLFFTTransform() = default;
		OpenGLFFTTransform(const std::filesystem::path&, GLuint, GLuint);
		virtual ~OpenGLFFTTransform() = default;

		void SetVariables(GLuint, GLuint);
		void SetAmplitudeTextureID(GLuint id);
		void SetPhaseTextureID(GLuint id);

		virtual void Init(const std::filesystem::path&) override;
		virtual void Execute() override;

	protected:
		GPUProgram m_GPUFFTProgram;
		std::filesystem::path m_SrcPath;
		GLuint m_AmplitudeTextureID;
		GLuint m_PhaseTextureID;
	};
}


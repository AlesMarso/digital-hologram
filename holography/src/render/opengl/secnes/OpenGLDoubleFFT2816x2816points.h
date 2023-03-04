#pragma once

#include <GL/glew.h>

#include <share/HoloIniFileController.h>

#include <render/opengl/secnes/IOpenGLScene.h>
#include <render/opengl/OpenGLTexture.h>
#include <render/opengl/shaders/Shader.h>
#include <render/opengl/shaders/GPUProgram.h>
#include <render/opengl/buffers/VertexArrayObject.h>
#include <render/opengl/buffers/VertexBufferObjectClass.h>

namespace rctx
{
	class OpenGLDoubleFFT2816x2816points : public IOpenGLScene
	{
	public:
		OpenGLDoubleFFT2816x2816points();
		virtual ~OpenGLDoubleFFT2816x2816points() = default;

		bool Load() override;
		bool Calculate() override;
		bool Draw() override;
		bool Close() override;

	private:
		OpenGLTexture m_TextureAmplitude;
		OpenGLTexture m_TexturePhase;


		GPUProgram m_ComputeProgram;
		GPUProgram m_RenderProgram;

		VertexBufferObjectClass<float> m_VBOAmplitude;
		VertexBufferObjectClass<float> m_VBOPhase;

		VertexArrayObject<float> m_VAOAmplitude;
		VertexArrayObject<float> m_VAOPhase;


		GLfloat m_VerticesAmplitude[16];
		GLfloat m_VerticesPhase[16];

	};
}

#pragma once

#include <GL/glew.h>

#include <share/HoloIniFileController.h>

#include <render/opengl/secnes/IOpenGLScene.h>
#include <render/opengl/OpenGLTexture.h>
#include <render/opengl/shaders/Shader.h>
#include <render/opengl/shaders/GPUProgram.h>
#include <render/opengl/buffers/VertexArrayObject.h>
#include <render/opengl/buffers/VertexBufferObjectClass.h>

#include <render/opengl/transform/OpenGLPSITransform.h>

namespace rctx
{
	class OpenGLFresnelScene : public IOpenGLScene
	{
	public:

		OpenGLFresnelScene();
		~OpenGLFresnelScene() = default;

		bool Load() override;
		bool Calculate() override;
		bool Draw() override;
		bool Close() override;

	/// Rendering
	private:
		OpenGLTexture m_PSIFirstTexture;
		OpenGLTexture m_PSISecondTexture;
		OpenGLTexture m_PSIThirdTexture;
		OpenGLTexture m_PSIFourthTexture;

		OpenGLTexture m_AmplitudeTexture;
		OpenGLTexture m_PhaseTexture;


		VertexBufferObjectClass<float> m_VBOAmplitude;
		VertexBufferObjectClass<float> m_VBOPhase;

		VertexArrayObject<float> m_VAOAmplitude;
		VertexArrayObject<float> m_VAOPhase;

		GLfloat m_VerticesAmplitude[16];
		GLfloat m_VerticesPhase[16];
		GPUProgram m_RenderProgram;

	private:
		OpenGLPSITransform m_PSITransform;
	};
}

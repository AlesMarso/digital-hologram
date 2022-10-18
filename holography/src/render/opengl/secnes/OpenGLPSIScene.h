#pragma once

#include <GL/glew.h>
#include <render/opengl/OpenGLTexture.h>
#include <render/opengl/secnes/IOpenGLScene.h>
#include <share/HoloIniFileController.h>
#include <gui/Color.h>

#include <render/opengl/shaders/Shader.h>
#include <render/opengl/shaders/GPUProgram.h>

namespace rctx
{
	class OpenGLPSIScene : public IOpenGLScene
	{
	public:
		OpenGLPSIScene();
		~OpenGLPSIScene();

		virtual bool Load() override;
		virtual bool Calculate() override;
		virtual bool Draw() override;
		virtual bool Close() override;

	private:
		GLuint m_VBO;
		GLuint m_VAO;
		GLfloat m_Vertices[16];
		OpenGLTexture m_PSIFirstTexture;
		OpenGLTexture m_ImgTexture;

		GPUProgram m_Program;
	};
}

#pragma once

#include <GL/glew.h>
#include <render/opengl/OpenGLTexture.h>
#include <render/opengl/IOpenGLScene.h>
#include <share/HoloIniFileController.h>
#include <gui/Color.h>

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
		GLfloat m_Vertices[8];
	};
}

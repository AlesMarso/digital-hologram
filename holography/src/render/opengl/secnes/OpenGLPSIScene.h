#pragma once

#include <GL/glew.h>
#include <render/opengl/OpenGLTexture.h>
#include <render/opengl/secnes/IOpenGLScene.h>
#include <share/HoloIniFileController.h>
#include <gui/Color.h>

#include <render/opengl/shaders/Shader.h>
#include <render/opengl/shaders/GPUProgram.h>
#include <render/opengl/buffers/VertexBufferObjectClass.h>
#include <render/opengl/buffers/VertexArrayObject.h>

#include <iostream>
#include <vector>

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
		GLuint m_VAO[2];
		GLfloat m_Vertices[16];
		OpenGLTexture m_PSITextures[4];

		VertexBufferObjectClass<float> m_VBO[2];
		VertexArrayObject<float> m_VAOs[2];

		GPUProgram m_Program;
	};
}

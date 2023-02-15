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
	class OpenGLFuorierScene : public IOpenGLScene
	{
	public:

		OpenGLFuorierScene();
		~OpenGLFuorierScene() = default;

		bool Load() override;
		bool Calculate() override;
		bool Draw() override;
		bool Close() override;

	private:
		OpenGLTexture m_Texture;

		GPUProgram m_ComputeProgram;
		GPUProgram m_ComputeProgram2;
		GPUProgram m_RenderProgram;

		VertexBufferObjectClass<float> m_VBO;
		VertexArrayObject<float> m_VAO;
		VertexBufferObjectClass<float> m_VBO1;

		GLfloat m_Vertices[16];
		int maxGroupX, maxGroupY, maxGroupZ;
	};
}

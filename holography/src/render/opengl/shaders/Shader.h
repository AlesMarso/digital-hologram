#pragma once

#include <GL/glew.h>
#include <string>
#include <filesystem>
#include <fstream>

namespace rctx
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		GLuint LoadSource(const std::filesystem::path&, GLenum, GLuint*);
		GLuint GetShaderID() const;

	private:
		GLuint m_ProgramID;
		GLuint m_ShaderID;
	};
}

#pragma once

#include <GL/glew.h>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace rctx
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		GLuint LoadSource(const std::filesystem::path&, GLenum, GLint*);
		GLuint GetShaderID() const;

	private:
		GLuint m_ProgramID;
		GLuint m_ShaderID;
	};
}

#pragma once

#include <render/opengl/shaders/Shader.h>
#include <filesystem>
#include <GL/glew.h>

namespace rctx
{
	class GPUProgram
	{
	public:
		GPUProgram();
		~GPUProgram();

		void LinkVertexShader(const std::filesystem::path&);
		void LinkFragmentShader(const std::filesystem::path&);

		GLint GetProgramID() const;
		void UseProgram();

		void SetUniform1i(const std::string&, int);

	private:
		Shader m_VertexShader;
		Shader m_FragmentShader;
		GLint m_ProgramID;
	};
}

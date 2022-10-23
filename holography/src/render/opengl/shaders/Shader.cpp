#include "Shader.h"

rctx::Shader::Shader()
	: m_ShaderID(-1), m_ProgramID(-1)
{
}

rctx::Shader::~Shader()
{
	if (m_ShaderID != -1 && m_ProgramID != -1)
	{
		glDetachShader(m_ProgramID, m_ShaderID);
		glDeleteShader(m_ShaderID);
	}
}

GLuint rctx::Shader::LoadSource(const std::filesystem::path& shadersrcpath, GLenum shadertype, GLint* programid)
{
	if (!programid)
		return -1;

	std::string sourceShader;
	std::ifstream shaderFile(shadersrcpath.c_str());

	if (!shaderFile)
		return -1;

	sourceShader.assign(std::istreambuf_iterator<char>(shaderFile), std::istreambuf_iterator<char>());

	m_ShaderID = glCreateShader(shadertype);
	const char* srcTemp = sourceShader.c_str();
	glShaderSource(m_ShaderID, 1, &srcTemp, NULL);
	glCompileShader(m_ShaderID);

	GLint compileStatus = GL_FALSE;
	glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(m_ShaderID, maxLength, &maxLength, &errorLog[0]);

		std::cout << errorLog.data() << std::endl;

		glDeleteShader(m_ShaderID);
		return -1;
	}

	if (*programid == -1)
		*programid = glCreateProgram();

	m_ProgramID = *programid;
	glAttachShader(m_ProgramID, m_ShaderID);
	glLinkProgram(m_ProgramID);

	GLint linkStatus = GL_FALSE;
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &infoLog[0]);

		std::cout << infoLog.data() << std::endl;

		glDeleteProgram(m_ProgramID);
		return -1;
	}

	return 1;
}

GLuint rctx::Shader::GetShaderID() const
{
	return m_ShaderID;
}

#include "GPUProgram.h"

rctx::GPUProgram::GPUProgram()
    : m_ProgramID(-1)
{
}

rctx::GPUProgram::~GPUProgram()
{
}

void rctx::GPUProgram::LinkVertexShader(const std::filesystem::path& vertexshader)
{
    m_VertexShader.LoadSource(vertexshader, GL_VERTEX_SHADER, &m_ProgramID);
}

void rctx::GPUProgram::LinkFragmentShader(const std::filesystem::path& fragmentshader)
{
    m_FragmentShader.LoadSource(fragmentshader, GL_FRAGMENT_SHADER, &m_ProgramID);
}

void rctx::GPUProgram::LinkComputeShader(const std::filesystem::path& computeshader)
{
    m_ComputeShader.LoadSource(computeshader, GL_COMPUTE_SHADER, &m_ProgramID);
}

GLint rctx::GPUProgram::GetProgramID() const
{
    return m_ProgramID;
}

void rctx::GPUProgram::UseProgram()
{
    if (m_ProgramID != -1)
        glUseProgram(m_ProgramID);
}

void rctx::GPUProgram::SetUniform1i(const std::string& variablename, int value)
{
    glUniform1i(glGetUniformLocation(m_ProgramID, variablename.c_str()), value);
}

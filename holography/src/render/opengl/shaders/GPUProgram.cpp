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

GLint rctx::GPUProgram::GetProgramID() const
{
    return m_ProgramID;
}

void rctx::GPUProgram::UseProgram()
{
    if (m_ProgramID != -1)
        glUseProgram(m_ProgramID);
}
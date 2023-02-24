#include "OpenGLDoubleFFT128x128points.h"

rctx::OpenGLDoubleFFT128x128points::OpenGLDoubleFFT128x128points()
{
    m_Vertices[0] = -0.95f;	m_Vertices[4] = -0.95f;	m_Vertices[8] = 0.95f;	m_Vertices[12] = 0.95f;
    m_Vertices[1] = -0.95f;	m_Vertices[5] = 0.95f;	m_Vertices[9] = 0.95f;	m_Vertices[13] = -0.95f;

    m_Vertices[2] = 0.0f;	m_Vertices[6] = 0.0f;	m_Vertices[10] = 1.0f;	m_Vertices[14] = 1.0f;
    m_Vertices[3] = 0.0f;	m_Vertices[7] = 1.0f;	m_Vertices[11] = 1.0f;	m_Vertices[15] = 0.0f;
}

bool rctx::OpenGLDoubleFFT128x128points::Load()
{
    std::vector<float> input;
    input.insert(input.end(), &m_Vertices[0], &m_Vertices[16]);

    m_VBO.SetData(input, GL_STATIC_DRAW);

    m_VAO.Bind();
    m_VBO.Bind();

    m_VAO.SetArray(0, 2, GL_FLOAT, GL_FALSE, 4, 0);
    m_VAO.SetArray(1, 2, GL_FLOAT, GL_FALSE, 4, 2);

    m_VBO.UnBind();
    m_VAO.UnBind();

    share::HoloIniFileController holoIniFile;

    m_Texture.CreateFromImage(holoIniFile.GetDoubleFFT128x128ImageFile());

    m_RenderProgram.LinkVertexShader(holoIniFile.GetVertexShaderFilePath());
    m_RenderProgram.LinkFragmentShader(holoIniFile.GetFragmentShaderFilePath());

    m_ComputeProgram.LinkComputeShader(holoIniFile.GetDoubleFFT128x128ComputeShaderFilePath());

    return true;
}

bool rctx::OpenGLDoubleFFT128x128points::Calculate()
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, m_Texture.GetTextureID());
    glBindImageTexture(0, m_Texture.GetTextureID(), 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);

    m_ComputeProgram.UseProgram();

    auto width = m_Texture.GetWidth();

    m_ComputeProgram.SetUniform1ui("PixelsX", static_cast<unsigned int>(width));
    uint32_t numLog2Levels = static_cast<uint32_t>(std::log2(width));
    m_ComputeProgram.SetUniform1ui("Log2Levels", static_cast<unsigned int>(numLog2Levels));

    glDispatchCompute(1, 1, 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);

    glBindImageTexture(0, 0, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);

    return true;
}

bool rctx::OpenGLDoubleFFT128x128points::Draw()
{
    glEnable(GL_TEXTURE_2D);

    m_RenderProgram.UseProgram();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Texture.GetTextureID());
    m_RenderProgram.SetUniform1i("u_Texture", 0);

    m_VAO.Bind();
    m_VAO.EnableArray(0);
    glDrawArrays(GL_QUADS, 0, 4);
    m_VAO.DisableArray(0);
    m_VAO.UnBind();
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);

    return true;
}

bool rctx::OpenGLDoubleFFT128x128points::Close()
{
    return true;
}

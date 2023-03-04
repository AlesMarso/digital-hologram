#include "OpenGLDoubleFFT2816x2816points.h"

rctx::OpenGLDoubleFFT2816x2816points::OpenGLDoubleFFT2816x2816points()
{
	m_VerticesAmplitude[0] = -0.95f;	m_VerticesAmplitude[4] = -0.95f;	m_VerticesAmplitude[8] = -0.05f;	m_VerticesAmplitude[12] = -0.05f;
	m_VerticesAmplitude[1] = -0.95f;	m_VerticesAmplitude[5] = 0.95f;	m_VerticesAmplitude[9] = 0.95f;	m_VerticesAmplitude[13] = -0.95f;

    m_VerticesPhase[0] = 0.05f;	m_VerticesPhase[4] = 0.05f;	m_VerticesPhase[8] = 0.95f;	m_VerticesPhase[12] = 0.95f;
    m_VerticesPhase[1] = -0.95f;	m_VerticesPhase[5] = 0.95f;	m_VerticesPhase[9] = 0.95f;	m_VerticesPhase[13] = -0.95f;

	m_VerticesAmplitude[2] = 0.0f;	m_VerticesAmplitude[6] = 0.0f;	m_VerticesAmplitude[10] = 1.0f;	m_VerticesAmplitude[14] = 1.0f;
	m_VerticesAmplitude[3] = 0.0f;	m_VerticesAmplitude[7] = 1.0f;	m_VerticesAmplitude[11] = 1.0f;	m_VerticesAmplitude[15] = 0.0f;

    m_VerticesPhase[2] = 0.0f;	m_VerticesPhase[6] = 0.0f;	m_VerticesPhase[10] = 1.0f;	m_VerticesPhase[14] = 1.0f;
    m_VerticesPhase[3] = 0.0f;	m_VerticesPhase[7] = 1.0f;	m_VerticesPhase[11] = 1.0f;	m_VerticesPhase[15] = 0.0f;
}

bool rctx::OpenGLDoubleFFT2816x2816points::Load()
{
    std::vector<float> ampl_array;
    ampl_array.insert(ampl_array.end(), &m_VerticesAmplitude[0], &m_VerticesAmplitude[16]);

    m_VBOAmplitude.SetData(ampl_array, GL_STATIC_DRAW);

    m_VAOAmplitude.Bind();
    m_VBOAmplitude.Bind();

    m_VAOAmplitude.SetArray(0, 2, GL_FLOAT, GL_FALSE, 4, 0);
    m_VAOAmplitude.SetArray(1, 2, GL_FLOAT, GL_FALSE, 4, 2);

    m_VBOAmplitude.UnBind();
    m_VAOAmplitude.UnBind();

    std::vector<float> phase_array;
    phase_array.insert(phase_array.end(), &m_VerticesPhase[0], &m_VerticesPhase[16]);

    m_VBOPhase.SetData(phase_array, GL_STATIC_DRAW);

    m_VAOPhase.Bind();
    m_VBOPhase.Bind();

    m_VAOPhase.SetArray(0, 2, GL_FLOAT, GL_FALSE, 4, 0);
    m_VAOPhase.SetArray(1, 2, GL_FLOAT, GL_FALSE, 4, 2);

    m_VBOPhase.UnBind();
    m_VAOPhase.UnBind();

    share::HoloIniFileController holoIniFile;

    m_TextureAmplitude.CreateFromImage(holoIniFile.GetDoubleFFT2816x2816ImageFile());
    m_TexturePhase.CreateFromImage(holoIniFile.GetDoubleFFT2816x2816ImageFile());

    m_RenderProgram.LinkVertexShader(holoIniFile.GetVertexShaderFilePath());
    m_RenderProgram.LinkFragmentShader(holoIniFile.GetFragmentShaderFilePath());

    m_ComputeProgram.LinkComputeShader(holoIniFile.GetDoubleFFT2816x2816ComputeShaderFilePath());

    return true;
}

bool rctx::OpenGLDoubleFFT2816x2816points::Calculate()
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, m_TextureAmplitude.GetTextureID());
    glBindImageTexture(0, m_TextureAmplitude.GetTextureID(), 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);

    m_ComputeProgram.UseProgram();

    auto width = m_TextureAmplitude.GetWidth();

    m_ComputeProgram.SetUniform1ui("PixelsX", static_cast<unsigned int>(width));

    glDispatchCompute(1, 1, 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);

    glBindImageTexture(0, 0, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);

    return true;
}

bool rctx::OpenGLDoubleFFT2816x2816points::Draw()
{
    glEnable(GL_TEXTURE_2D);

    m_RenderProgram.UseProgram();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_TextureAmplitude.GetTextureID());
    m_RenderProgram.SetUniform1i("u_Texture", 0);

    m_VAOAmplitude.Bind();
    m_VAOAmplitude.EnableArray(0);
    glDrawArrays(GL_QUADS, 0, 4);
    m_VAOAmplitude.DisableArray(0);
    m_VAOAmplitude.UnBind();

    glBindTexture(GL_TEXTURE_2D, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_TexturePhase.GetTextureID());
    m_RenderProgram.SetUniform1i("u_Texture", 1);
    m_VAOPhase.Bind();
    m_VAOPhase.EnableArray(0);
    glDrawArrays(GL_QUADS, 0, 4);
    m_VAOPhase.DisableArray(0);
    m_VAOPhase.UnBind();

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);

    return true;
}

bool rctx::OpenGLDoubleFFT2816x2816points::Close()
{
	return true;
}

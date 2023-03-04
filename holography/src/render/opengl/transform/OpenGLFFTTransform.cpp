#include "OpenGLFFTTransform.h"

rctx::OpenGLFFTTransform::OpenGLFFTTransform(const std::filesystem::path& src, GLuint ampl, GLuint phase)
	: m_SrcPath(src)
{
	Init(m_SrcPath);
	SetVariables(ampl, phase);
}

void rctx::OpenGLFFTTransform::SetVariables(GLuint ampl, GLuint phase)
{
	m_AmplitudeTextureID = ampl;
	m_PhaseTextureID = phase;
}

void rctx::OpenGLFFTTransform::Init(const std::filesystem::path&)
{
	m_GPUFFTProgram.LinkComputeShader(m_SrcPath);
}

void rctx::OpenGLFFTTransform::Execute()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,m_AmplitudeTextureID);
	glBindImageTexture(0, m_AmplitudeTextureID, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);

	m_GPUFFTProgram.UseProgram();

	glDispatchCompute(1, 1, 1);
	glMemoryBarrier(GL_ALL_BARRIER_BITS);

	glBindImageTexture(0, 0, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
}

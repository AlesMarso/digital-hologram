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

void rctx::OpenGLFFTTransform::SetAmplitudeTextureID(GLuint id)
{
	m_AmplitudeTextureID = id;
}

void rctx::OpenGLFFTTransform::SetPhaseTextureID(GLuint id)
{
	m_PhaseTextureID = id;
}

void rctx::OpenGLFFTTransform::Init(const std::filesystem::path& path)
{
	m_GPUFFTProgram.LinkComputeShader(path);

	glGenQueries(1, &m_StartQuery);
	glGenQueries(1, &m_EndQuery);
}

void rctx::OpenGLFFTTransform::Execute()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,m_AmplitudeTextureID);
	glBindImageTexture(0, m_AmplitudeTextureID, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);

	glBindTexture(GL_TEXTURE_2D, m_PhaseTextureID);
	glBindImageTexture(1, m_PhaseTextureID, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);

	m_GPUFFTProgram.UseProgram();

	glMemoryBarrier(GL_ALL_BARRIER_BITS);

	glQueryCounter(m_StartQuery, GL_TIMESTAMP);
	glDispatchCompute(1, 1, 1);
	glQueryCounter(m_EndQuery, GL_TIMESTAMP);

	glGetQueryObjectui64v(m_StartQuery, GL_QUERY_RESULT, &m_StartTime);
	glGetQueryObjectui64v(m_EndQuery, GL_QUERY_RESULT, &m_EndTime);

	m_ElapsedTime = m_EndTime - m_StartTime;

	glBindImageTexture(0, 0, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
}

#include "OpenGLPSITransform.h"

rctx::OpenGLPSITransform::OpenGLPSITransform()
{
	glGenQueries(1, &m_StartQuery);
	glGenQueries(1, &m_EndQuery);
}

rctx::OpenGLPSITransform::OpenGLPSITransform(const std::filesystem::path& src)
	: m_SrcPath(src)
{
	Init(m_SrcPath);
}

rctx::OpenGLPSITransform::~OpenGLPSITransform()
{
	glDeleteQueries(1, &m_StartQuery);
	glDeleteQueries(1, &m_EndQuery);
}

void rctx::OpenGLPSITransform::SetFirstPSIImage(GLuint id)
{
	m_FirstPSIImage = id;
}

void rctx::OpenGLPSITransform::SetSecondPSIImage(GLuint id)
{
	m_SecondPSIImage = id;
}

void rctx::OpenGLPSITransform::SetThirdPSIImage(GLuint id)
{
	m_ThirdPSIImage = id;
}

void rctx::OpenGLPSITransform::SetFourthPSIImage(GLuint id)
{
	m_FourthPSIImage = id;
}

void rctx::OpenGLPSITransform::SetAmplitudeImage(GLuint id)
{
	m_AmpltudeImage = id;
}

void rctx::OpenGLPSITransform::SetPhaseImage(GLuint id)
{
	m_PhaseImage = id;
}

void rctx::OpenGLPSITransform::SetPhaseOne(float val)
{
	m_PhaseOne = val;
}

void rctx::OpenGLPSITransform::SetPhaseTwo(float val)
{
	m_PhaseTwo = val;
}

void rctx::OpenGLPSITransform::SetPhaseThree(float val)
{
	m_PhaseThree = val;
}

void rctx::OpenGLPSITransform::SetPhaseFour(float val)
{
	m_PhaseThree = val;
}

void rctx::OpenGLPSITransform::Init(const std::filesystem::path& src)
{
	m_PSIProgram.LinkComputeShader(src);
}

void rctx::OpenGLPSITransform::Execute()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, m_FirstPSIImage);
	glBindImageTexture(0, m_FirstPSIImage, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);

	glBindTexture(GL_TEXTURE_2D, m_SecondPSIImage);
	glBindImageTexture(1, m_SecondPSIImage, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);

	glBindTexture(GL_TEXTURE_2D, m_ThirdPSIImage);
	glBindImageTexture(2, m_ThirdPSIImage, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);

	glBindTexture(GL_TEXTURE_2D, m_FourthPSIImage);
	glBindImageTexture(3, m_FourthPSIImage, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);

	glBindTexture(GL_TEXTURE_2D, m_AmpltudeImage);
	glBindImageTexture(4, m_AmpltudeImage, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);

	glBindTexture(GL_TEXTURE_2D, m_PhaseImage);
	glBindImageTexture(5, m_PhaseImage, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);

	m_PSIProgram.UseProgram();
	
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

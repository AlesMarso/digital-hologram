#include "OpenGLExpTransform.h"

rctx::OpenGLExpTransform::OpenGLExpTransform(const std::filesystem::path& src, GLuint ampl, GLuint phase)
	: m_SrcPath(src), m_AmplitudeImage(ampl), m_PhaseImage(phase)
{
	Init(m_SrcPath);
}

void rctx::OpenGLExpTransform::Init(const std::filesystem::path& src)
{
	m_ExpProgram.LinkComputeShader(src);
}

void rctx::OpenGLExpTransform::Execute()
{
}

#include "OpenGLDoubleFFT2816x2816points.h"

rctx::OpenGLDoubleFFT2816x2816points::OpenGLDoubleFFT2816x2816points()
{
	m_Vertices[0] = -0.95f;	m_Vertices[4] = -0.95f;	m_Vertices[8] = 0.95f;	m_Vertices[12] = 0.95f;
	m_Vertices[1] = -0.95f;	m_Vertices[5] = 0.95f;	m_Vertices[9] = 0.95f;	m_Vertices[13] = -0.95f;

	m_Vertices[2] = 0.0f;	m_Vertices[6] = 0.0f;	m_Vertices[10] = 1.0f;	m_Vertices[14] = 1.0f;
	m_Vertices[3] = 0.0f;	m_Vertices[7] = 1.0f;	m_Vertices[11] = 1.0f;	m_Vertices[15] = 0.0f;
}

bool rctx::OpenGLDoubleFFT2816x2816points::Load()
{
	return true;
}

bool rctx::OpenGLDoubleFFT2816x2816points::Calculate()
{
	return true;
}

bool rctx::OpenGLDoubleFFT2816x2816points::Draw()
{
	return true;
}

bool rctx::OpenGLDoubleFFT2816x2816points::Close()
{
	return true;
}

#pragma once

#include <filesystem>
#include <include/GL/glew.h>

constexpr auto M_10E9 = 1000000000;

namespace rctx
{
	class IOpenGLTransform
	{
	public:
		IOpenGLTransform() : m_StartQuery(0), m_EndQuery(0), m_StartTime(0), m_EndTime(0), m_ElapsedTime(0) {}
		~IOpenGLTransform() = default;

		virtual void Init(const std::filesystem::path&) = 0;
		virtual void Execute() = 0;
		GLuint64 GetElapsedTime() const { return m_ElapsedTime; }

	protected:
		GLuint    m_StartQuery, m_EndQuery;
		GLuint64 m_StartTime, m_EndTime;
		GLuint64 m_ElapsedTime;
	};
}

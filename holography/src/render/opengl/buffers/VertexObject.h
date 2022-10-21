#pragma once

#include <GL/glew.h>

namespace rctx
{
	class VertexObject
	{
	public:
		VertexObject() = default;
		~VertexObject() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		GLuint GetID() const { return m_ID; }
		bool IsBind() const { return m_IsBind; }

	protected:
		GLuint	m_ID;
		bool	m_IsBind;
	};
}

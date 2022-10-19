#pragma once

#include <GL/glew.h>
#include <vector>

namespace rctx
{
	template<typename T, GLenum U>
	class VertexBufferObjectClass
	{
	public:
		VertexBufferObjectClass();
		~VertexBufferObjectClass();

		GLuint GetBufferID() const;

		void SetData(const std::vector<T>&);

		void Bind();
		void UnBind();
		bool IsBind() const;

	private:
		GLuint m_idVBO;
		bool m_IsBind;
		GLsizeiptr m_Size;
	};

	template<typename T, GLenum U>
	inline VertexBufferObjectClass<T, U>::VertexBufferObjectClass()
	{
		glGenBuffers(1, &m_idVBO);
	}

	template<typename T, GLenum U>
	inline VertexBufferObjectClass<T, U>::~VertexBufferObjectClass()
	{
		glDeleteBuffers(1, &m_idVBO);
	}

	template<typename T, GLenum U>
	inline GLuint VertexBufferObjectClass<T, U>::GetBufferID() const
	{
		return m_idVBO;
	}

	template<typename T, GLenum U>
	inline void VertexBufferObjectClass<T, U>::SetData(const std::vector<T>& input)
	{
		m_Size = input.size() * sizeof(T);

		Bind();
		glBufferData(GL_ARRAY_BUFFER, m_Size, &input[0], U);
		UnBind();
	}

	template<typename T, GLenum U>
	inline void VertexBufferObjectClass<T, U>::Bind()
	{
		m_IsBind = true;
		glBindBuffer(GL_ARRAY_BUFFER, m_idVBO);
	}

	template<typename T, GLenum U>
	inline void VertexBufferObjectClass<T, U>::UnBind()
	{
		m_IsBind = false;
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	template<typename T, GLenum U>
	inline bool VertexBufferObjectClass<T, U>::IsBind() const
	{
		return m_IsBind;
	}
}

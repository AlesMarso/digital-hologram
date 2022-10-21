#pragma once

#include <render/opengl/buffers/VertexObject.h>
#include <vector>

namespace rctx
{
	template<typename T>
	class VertexBufferObjectClass : public VertexObject
	{
	public:
		VertexBufferObjectClass();
		~VertexBufferObjectClass();

		void SetData(const std::vector<T>&, GLenum);

		void Bind() override;
		void UnBind() override;

	private:
		GLsizeiptr m_Size;
	};

	template<typename T>
	inline VertexBufferObjectClass<T>::VertexBufferObjectClass()
	{
		glGenBuffers(1, &m_ID);
	}

	template<typename T>
	inline VertexBufferObjectClass<T>::~VertexBufferObjectClass()
	{
		glDeleteBuffers(1, &m_ID);
	}

	template<typename T>
	inline void VertexBufferObjectClass<T>::SetData(const std::vector<T>& input, GLenum usage)
	{
		m_Size = input.size() * sizeof(T);

		Bind();
		glBufferData(GL_ARRAY_BUFFER, m_Size, &input[0], usage);
		UnBind();
	}

	template<typename T>
	inline void VertexBufferObjectClass<T>::Bind()
	{
		m_IsBind = true;
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	template<typename T>
	inline void VertexBufferObjectClass<T>::UnBind()
	{
		m_IsBind = false;
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

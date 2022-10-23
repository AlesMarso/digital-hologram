#pragma once

#include <render/opengl/buffers/VertexObject.h>

namespace rctx
{
	template<typename T>
	class VertexArrayObject : public VertexObject
	{
	public:
		VertexArrayObject();
		~VertexArrayObject();

		void Bind() override;
		void UnBind() override;

		void EnableArray(int);
		void DisableArray(int);

		void SetArray(int, int, GLenum, GLboolean, int, int);
	};

	template<typename T>
	inline VertexArrayObject<T>::VertexArrayObject()
	{
		glGenVertexArrays(1, &m_ID);
	}

	template<typename T>
	inline VertexArrayObject<T>::~VertexArrayObject()
	{
		glDeleteVertexArrays(1, &m_ID);
	}

	template<typename T>
	inline void VertexArrayObject<T>::Bind()
	{
		m_IsBind = true;
		glBindVertexArray(m_ID);
	}

	template<typename T>
	inline void VertexArrayObject<T>::UnBind()
	{
		m_IsBind = false;
		glBindVertexArray(0);
	}

	template<typename T>
	inline void VertexArrayObject<T>::EnableArray(int index)
	{
		glEnableVertexArrayAttrib(m_ID, index);
	}

	template<typename T>
	inline void VertexArrayObject<T>::DisableArray(int index)
	{
		glEnableVertexArrayAttrib(m_ID, index);
	}

	template<typename T>
	inline void VertexArrayObject<T>::SetArray(int index, int size, GLenum type, GLboolean normalized, int stride, int begin)
	{
		EnableArray(index);
		glVertexAttribPointer(index, size, type, normalized, stride * sizeof(T), (void*)(begin * sizeof(T)));
	}
}

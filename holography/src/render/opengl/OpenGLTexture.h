#pragma once

#include <windows.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <filesystem>
#include <gdiplus.h>

namespace rctx
{
	class OpenGLTexture
	{
	public:
		OpenGLTexture();
		~OpenGLTexture();

		GLuint GetTextureID() const;
		int GetWidth() const;
		int GetHeight() const;

		bool CreateFromImage(const std::filesystem::path&);

	private:
		GLuint m_TextureID;
		int m_Width;
		int m_Height;
	};
}

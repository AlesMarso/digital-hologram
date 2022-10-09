#include "OpenGLTexture.h"

rctx::OpenGLTexture::OpenGLTexture()
	: m_TextureID(0),
	m_Width(0),
	m_Height(0)
{
}

rctx::OpenGLTexture::~OpenGLTexture()
{
	if (m_TextureID)
		glDeleteTextures(1, &m_TextureID);
}

GLuint rctx::OpenGLTexture::GetTextureID() const
{
	return m_TextureID;
}

int rctx::OpenGLTexture::GetWidth() const
{
	return m_Width;
}

int rctx::OpenGLTexture::GetHeight() const
{
	return m_Height;
}

bool rctx::OpenGLTexture::CreateFromImage(const std::filesystem::path& imgPath)
{
	Gdiplus::Bitmap* bmp = new Gdiplus::Bitmap(imgPath.generic_wstring().c_str(), FALSE);

	m_Width = bmp->GetWidth();
	m_Height = bmp->GetHeight();

	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	auto bitmapData = new Gdiplus::BitmapData;
	Gdiplus::Rect rect(0, 0, m_Width, m_Height);

	bmp->LockBits(&rect, Gdiplus::ImageLockModeRead, bmp->GetPixelFormat(), bitmapData);

	auto* pixels = static_cast<unsigned*>(bitmapData->Scan0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	bmp->UnlockBits(bitmapData);

	glDisable(GL_TEXTURE_2D);

	delete bmp;

	return true;
}

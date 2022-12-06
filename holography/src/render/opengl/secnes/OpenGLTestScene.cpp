#include "OpenGLTestScene.h"

bool rctx::OpenGLTestScene::Load()
{
	share::HoloIniFileController holoIniFile;

	m_PSIFirstTexture.CreateFromImage(holoIniFile.GetPSIFirstImage());
	m_PSISecondTexture.CreateFromImage(holoIniFile.GetPSISecondImage());
	m_PSIThirdTexture.CreateFromImage(holoIniFile.GetPSIThirdImage());
	m_PSIFourthTexture.CreateFromImage(holoIniFile.GetPSIFourthImage());

	white = 0xffffff;

	return true;
}

bool rctx::OpenGLTestScene::Calculate()
{
	return true;
}

bool rctx::OpenGLTestScene::Draw()
{
	glColor3f(white.fRed(), white.fGreen(), white.fBlue());

	glEnable(GL_TEXTURE_2D);

	// First PSI Image
	glBindTexture(GL_TEXTURE_2D, m_PSIFirstTexture.GetTextureID());
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0.0f, 0.0f);
		glVertex2f(-0.95f, -0.95f);

		glTexCoord2d(0.0f, 1.0f);
		glVertex2f(-0.05f, -0.95f);

		glTexCoord2d(1.0f, 1.0f);
		glVertex2f(-0.05f, -0.05f);

		glTexCoord2d(1.0f, 0.0f);
		glVertex2f(-0.95f, -0.05f);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);

	// Second PSI Image
	glBindTexture(GL_TEXTURE_2D, m_PSISecondTexture.GetTextureID());
	glBegin(GL_QUADS);
	{
		glTexCoord2d(1.0f, 1.0f);
		glVertex2f(0.05f, -0.95f);

		glTexCoord2d(0.0f, 1.0f);
		glVertex2f(0.95f, -0.95f);

		glTexCoord2d(0.0f, 0.0f);
		glVertex2f(0.95f, -0.05f);

		glTexCoord2d(1.0f, 0.0f);
		glVertex2f(0.05f, -0.05f);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// Third PSI Image
	glBindTexture(GL_TEXTURE_2D, m_PSIThirdTexture.GetTextureID());
	glBegin(GL_QUADS);
	{
		glTexCoord2d(1.0f, 1.0f);
		glVertex2f(0.05f, 0.05f);

		glTexCoord2d(0.0f, 1.0f);
		glVertex2f(0.95f, 0.05f);

		glTexCoord2d(0.0f, 0.0f);
		glVertex2f(0.95f, 0.95f);

		glTexCoord2d(1.0f, 0.0f);
		glVertex2f(0.05f, 0.95f);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// Fourth PSI Image
	glBindTexture(GL_TEXTURE_2D, m_PSIFourthTexture.GetTextureID());
	glBegin(GL_QUADS);
	{
		glTexCoord2d(1.0f, 1.0f);
		glVertex2f(-0.95f, 0.05f);

		glTexCoord2d(0.0f, 1.0f);
		glVertex2f(-0.05f, 0.05f);

		glTexCoord2d(0.0f, 0.0f);
		glVertex2f(-0.05f, 0.95f);

		glTexCoord2d(1.0f, 0.0f);
		glVertex2f(-0.95f, 0.95f);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);

	return true;
}

bool rctx::OpenGLTestScene::Close()
{
	return true;
}

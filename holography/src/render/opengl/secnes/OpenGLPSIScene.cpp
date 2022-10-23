#include "OpenGLPSIScene.h"

rctx::OpenGLPSIScene::OpenGLPSIScene()
{
	m_Vertices[0] = -0.95f;	m_Vertices[4] = -0.95f;	m_Vertices[8] = -0.05f;	m_Vertices[12] = -0.05f;
	m_Vertices[1] = -0.95f;	m_Vertices[5] = 0.95f;	m_Vertices[9] = 0.95f;	m_Vertices[13] = -0.95f;

	m_Vertices[2] = 0.0f;	m_Vertices[6] = 0.0f;	m_Vertices[10] = 1.0f;	m_Vertices[14] = 1.0f;
	m_Vertices[3] = 0.0f;	m_Vertices[7] = 1.0f;	m_Vertices[11] = 1.0f;	m_Vertices[15] = 0.0f;
}

rctx::OpenGLPSIScene::~OpenGLPSIScene()
{
}

template< typename T> void sizeOfT(std::vector<T> in) { std::cout << in.size() * sizeof(T) << std::endl; };

bool rctx::OpenGLPSIScene::Load()
{
	std::vector<float> input[2];
	input[0].insert(input[0].end(), &m_Vertices[0], &m_Vertices[16]);

	m_Vertices[0] = 0.95f;	m_Vertices[4] = 0.95f; m_Vertices[8] = 0.05f; m_Vertices[12] = 0.05f;
	m_Vertices[1] = -0.95f; m_Vertices[5] = 0.95f; m_Vertices[9] = 0.95f; m_Vertices[13] = -0.95f;

	input[1].insert(input[1].end(), &m_Vertices[0], &m_Vertices[16]);

	for (int i = 0; i < 2; i++)
	{
		m_VBO[i].SetData(input[i], GL_STATIC_DRAW);

		m_VAOs[i].Bind();
		m_VBO[i].Bind();

		m_VAOs[i].SetArray(0, 2, GL_FLOAT, GL_FALSE, 4, 0);
		m_VAOs[i].SetArray(1, 2, GL_FLOAT, GL_FALSE, 4, 2);

		m_VBO[i].UnBind();
		m_VAOs[i].UnBind();
	}

	share::HoloIniFileController holoIniFile;

	m_Program.LinkVertexShader(holoIniFile.GetVertexShaderFilePath());
	m_Program.LinkFragmentShader(holoIniFile.GetFragmentShaderFilePath());

	m_PSITextures[0].CreateFromImage(holoIniFile.GetPSIFirstImage());
	m_PSITextures[1].CreateFromImage(holoIniFile.GetPSISecondImage());
	m_PSITextures[2].CreateFromImage(holoIniFile.GetPSIThirdImage());
	m_PSITextures[3].CreateFromImage(holoIniFile.GetPSIFourthImage());

	return true;
}

bool rctx::OpenGLPSIScene::Calculate()
{
	return true;
}

bool rctx::OpenGLPSIScene::Draw()
{
	glEnable(GL_TEXTURE_2D);

	m_Program.UseProgram();

	for (int i = 0; i < 2; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_PSITextures[i].GetTextureID());
		m_Program.SetUniform1i("u_Texture", i);

		m_VAOs[i].Bind();
		m_VAOs[i].EnableArray(0);
		glDrawArrays(GL_QUADS, 0, 4);
		m_VAOs[i].DisableArray(0);
		m_VAOs[i].UnBind();
	}

	glDisable(GL_TEXTURE_2D);

	return true;
}

bool rctx::OpenGLPSIScene::Close()
{
	return true;
}

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
	std::vector<float> input;
	input.insert(input.end(), &m_Vertices[0], &m_Vertices[16]);

	m_VBO[0].SetData(input, GL_STATIC_DRAW);

	glGenVertexArrays(2, m_VAO);
	glBindVertexArray(m_VAO[0]);
	m_VBO[0].Bind();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	m_VBO[0].UnBind();
	glBindVertexArray(0);

	input.clear();

	m_Vertices[0] = 0.95f;	m_Vertices[4] = 0.95f; m_Vertices[8] = 0.05f; m_Vertices[12] = 0.05f;
	m_Vertices[1] = -0.95f; m_Vertices[5] = 0.95f; m_Vertices[9] = 0.95f; m_Vertices[13] = -0.95f;

	input.insert(input.end(), &m_Vertices[0], &m_Vertices[16]);

	m_VBO[1].SetData(input, GL_STATIC_DRAW);

	glBindVertexArray(m_VAO[1]);
	m_VBO[1].Bind();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	m_VBO[1].UnBind();
	glBindVertexArray(0);

	share::HoloIniFileController holoIniFile;

	m_Program.LinkVertexShader(holoIniFile.GetVertexShaderFilePath());
	m_Program.LinkFragmentShader(holoIniFile.GetFragmentShaderFilePath());

	m_PSIFirstTexture[0].CreateFromImage(holoIniFile.GetPSIFirstImage());
	m_PSIFirstTexture[1].CreateFromImage(holoIniFile.GetImageFileName());

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
		glBindVertexArray(m_VAO[i]);

		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_PSIFirstTexture[i].GetTextureID());

		m_Program.SetUniform1i("u_Texture", i);

		glEnableVertexAttribArray(0);
		glDrawArrays(GL_QUADS, 0, 4);
		glDisableVertexAttribArray(0);

		glBindVertexArray(0);
	}

	glDisable(GL_TEXTURE_2D);

	return true;
}

bool rctx::OpenGLPSIScene::Close()
{
	return true;
}

#include "OpenGLPSIScene.h"

rctx::OpenGLPSIScene::OpenGLPSIScene()
	: m_VBO(-1), m_VAO(-1)
{
	m_Vertices[0] = -0.95f;
	m_Vertices[1] = -0.95f;

	m_Vertices[2] = 0.0f;
	m_Vertices[3] = 0.0f;

	m_Vertices[4] = -0.95f;
	m_Vertices[5] = 0.95f;

	m_Vertices[6] = 0.0f;
	m_Vertices[7] = 1.0f;

	m_Vertices[8] = 0.95f;
	m_Vertices[9] = 0.95f;

	m_Vertices[10] = 1.0f;
	m_Vertices[11] = 1.0f;

	m_Vertices[12] = 0.95f;
	m_Vertices[13] = -0.95f;

	m_Vertices[14] = 1.0f;
	m_Vertices[15] = 0.0f;
}

rctx::OpenGLPSIScene::~OpenGLPSIScene()
{
}

bool rctx::OpenGLPSIScene::Load()
{
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	share::HoloIniFileController holoIniFile;

	m_Program.LinkVertexShader(holoIniFile.GetVertexShaderFilePath());
	m_Program.LinkFragmentShader(holoIniFile.GetFragmentShaderFilePath());
	m_PSIFirstTexture.CreateFromImage(holoIniFile.GetPSIFirstImage());

	return true;
}

bool rctx::OpenGLPSIScene::Calculate()
{
	return true;
}

bool rctx::OpenGLPSIScene::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindVertexArray(m_VAO);

	m_Program.UseProgram();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_PSIFirstTexture.GetTextureID());
	m_Program.SetUniform1i("u_Texture", 0);

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableVertexAttribArray(0);

	glBindVertexArray(0);
	glDisable(GL_TEXTURE_2D);

	return true;
}

bool rctx::OpenGLPSIScene::Close()
{
	return true;
}

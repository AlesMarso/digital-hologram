#include "OpenGLPSIScene.h"

rctx::OpenGLPSIScene::OpenGLPSIScene()
	: m_VBO(-1), m_VAO(-1), m_ProgramID(-1)
{
	m_Vertices[0] = -0.95f;
	m_Vertices[1] = -0.95f;

	m_Vertices[2] = -0.95f;
	m_Vertices[3] = 0.95f;

	m_Vertices[4] = 0.95f;
	m_Vertices[5] = 0.95f;

	m_Vertices[6] = 0.95f;
	m_Vertices[7] = -0.95f;
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

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	share::HoloIniFileController holoIniFile;

	m_VertexShader.LoadSource(holoIniFile.GetVertexShaderFilePath(), GL_VERTEX_SHADER, &m_ProgramID);
	m_FragmentShader.LoadSource(holoIniFile.GetFragmentShaderFilePath(), GL_FRAGMENT_SHADER, &m_ProgramID);

	return true;
}

bool rctx::OpenGLPSIScene::Calculate()
{
	return true;
}

bool rctx::OpenGLPSIScene::Draw()
{
	if(m_ProgramID != -1)
		glUseProgram(m_ProgramID);

	glBindVertexArray(m_VAO);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableVertexAttribArray(0);

	return true;
}

bool rctx::OpenGLPSIScene::Close()
{
	return true;
}

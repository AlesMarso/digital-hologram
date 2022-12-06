#include "OpenGLFuorierScene.h"

rctx::OpenGLFuorierScene::OpenGLFuorierScene()
{
    m_Vertices[0] = -0.95f;	m_Vertices[4] = -0.95f;	m_Vertices[8] = 0.95f;	m_Vertices[12] = 0.95f;
    m_Vertices[1] = -0.95f;	m_Vertices[5] = 0.95f;	m_Vertices[9] = 0.95f;	m_Vertices[13] = -0.95f;

    m_Vertices[2] = 0.0f;	m_Vertices[6] = 0.0f;	m_Vertices[10] = 1.0f;	m_Vertices[14] = 1.0f;
    m_Vertices[3] = 0.0f;	m_Vertices[7] = 1.0f;	m_Vertices[11] = 1.0f;	m_Vertices[15] = 0.0f;
}

bool rctx::OpenGLFuorierScene::Load()
{
    std::vector<float> input;
    input.insert(input.end(), &m_Vertices[0], &m_Vertices[16]);

    m_VBO.SetData(input, GL_STATIC_DRAW);

    m_VAO.Bind();
    m_VBO.Bind();

    m_VAO.SetArray(0, 2, GL_FLOAT, GL_FALSE, 4, 0);
    m_VAO.SetArray(1, 2, GL_FLOAT, GL_FALSE, 4, 2);

    m_VBO.UnBind();
    m_VAO.UnBind();

    share::HoloIniFileController holoIniFile;

    m_Texture.CreateFromImage(holoIniFile.GetPSIFirstImage());

    m_RenderProgram.LinkVertexShader(holoIniFile.GetVertexShaderFilePath());
    m_RenderProgram.LinkFragmentShader(holoIniFile.GetFragmentShaderFilePath());

    m_ComputeProgram.LinkComputeShader(holoIniFile.GetComputeShaderFilePath());

    int maxX, maxY, maxZ, maxItemsPerGroup;

    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &maxX);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &maxY);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &maxZ);
    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &maxItemsPerGroup);

    std::cout << "Max work group size X: " << maxX << std::endl;
    std::cout << "Max work group size Y: " << maxY << std::endl;
    std::cout << "Max work group size Z: " << maxZ << std::endl;
    std::cout << "Max work group items: " << maxItemsPerGroup << std::endl;

    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &maxGroupX);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &maxGroupY);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &maxGroupZ);

    std::cout << "Max work group count X: " << maxGroupX << std::endl;
    std::cout << "Max work group count Y: " << maxGroupY << std::endl;
    std::cout << "Max work group count Z: " << maxGroupZ << std::endl;

    return true;
}

bool rctx::OpenGLFuorierScene::Calculate()
{
    //m_ComputeProgram.UseProgram();
    //m_ComputeProgram.SetUniform1ui("PixelsX", static_cast<unsigned int>(m_Texture.GetWidth()));
    //uint32_t numLog2Levels = static_cast<uint32_t>(std::log2(static_cast<double>(m_Texture.GetWidth())));
    //m_ComputeProgram.SetUniform1ui("Log2Levels", static_cast<unsigned int>(numLog2Levels));
    //
    //glEnable(GL_TEXTURE_2D);
    //
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, m_Texture.GetTextureID());
    //glBindImageTexture(0, m_Texture.GetTextureID(), 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);
    //glDispatchCompute(1, 4, 1);
    //glMemoryBarrier(GL_ALL_BARRIER_BITS);
    //glBindImageTexture(0, 0, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);
    //
    //glBindTexture(GL_TEXTURE_2D, 0);
    //
    //glDisable(GL_TEXTURE_2D);

    return true;
}

bool rctx::OpenGLFuorierScene::Draw()
{
    glEnable(GL_TEXTURE_2D);

    m_RenderProgram.UseProgram();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Texture.GetTextureID());
    m_RenderProgram.SetUniform1i("u_Texture", 0);

    m_VAO.Bind();
    m_VAO.EnableArray(0);
    glDrawArrays(GL_QUADS, 0, 4);
    m_VAO.DisableArray(0);
    m_VAO.UnBind();
    //glRotatef(90, 1.0f, 1.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);

    return true;
}

bool rctx::OpenGLFuorierScene::Close()
{
    return true;
}

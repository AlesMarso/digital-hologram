#include "OpenGLFresnelScene.h"

rctx::OpenGLFresnelScene::OpenGLFresnelScene()
{
    m_VerticesAmplitude[0] = -0.95f; m_VerticesAmplitude[4] = -0.95f; m_VerticesAmplitude[8] = -0.05f; m_VerticesAmplitude[12] = -0.05f;
    m_VerticesAmplitude[1] = -0.95f; m_VerticesAmplitude[5] = 0.95f; m_VerticesAmplitude[9] = 0.95f; m_VerticesAmplitude[13] = -0.95f;

    m_VerticesPhase[0] = 0.05f; m_VerticesPhase[4] = 0.05f; m_VerticesPhase[8] = 0.95f; m_VerticesPhase[12] = 0.95f;
    m_VerticesPhase[1] = -0.95f; m_VerticesPhase[5] = 0.95f; m_VerticesPhase[9] = 0.95f; m_VerticesPhase[13] = -0.95f;

    m_VerticesAmplitude[2] = 0.0f; m_VerticesAmplitude[6] = 0.0f; m_VerticesAmplitude[10] = 1.0f; m_VerticesAmplitude[14] = 1.0f;
    m_VerticesAmplitude[3] = 0.0f; m_VerticesAmplitude[7] = 1.0f; m_VerticesAmplitude[11] = 1.0f; m_VerticesAmplitude[15] = 0.0f;

    m_VerticesPhase[2] = 0.0f; m_VerticesPhase[6] = 0.0f; m_VerticesPhase[10] = 1.0f; m_VerticesPhase[14] = 1.0f;
    m_VerticesPhase[3] = 0.0f; m_VerticesPhase[7] = 1.0f; m_VerticesPhase[11] = 1.0f; m_VerticesPhase[15] = 0.0f;
}

bool rctx::OpenGLFresnelScene::Load()
{
    std::vector<float> ampl_array;
    ampl_array.insert(ampl_array.end(), &m_VerticesAmplitude[0], &m_VerticesAmplitude[16]);

    m_VBOAmplitude.SetData(ampl_array, GL_STATIC_DRAW);

    m_VAOAmplitude.Bind();
    m_VBOAmplitude.Bind();

    m_VAOAmplitude.SetArray(0, 2, GL_FLOAT, GL_FALSE, 4, 0);
    m_VAOAmplitude.SetArray(1, 2, GL_FLOAT, GL_FALSE, 4, 2);

    m_VBOAmplitude.UnBind();
    m_VAOAmplitude.UnBind();

    std::vector<float> phase_array;
    phase_array.insert(phase_array.end(), &m_VerticesPhase[0], &m_VerticesPhase[16]);

    m_VBOPhase.SetData(phase_array, GL_STATIC_DRAW);

    m_VAOPhase.Bind();
    m_VBOPhase.Bind();

    m_VAOPhase.SetArray(0, 2, GL_FLOAT, GL_FALSE, 4, 0);
    m_VAOPhase.SetArray(1, 2, GL_FLOAT, GL_FALSE, 4, 2);

    m_VBOPhase.UnBind();
    m_VAOPhase.UnBind();

    share::HoloIniFileController holoIniFile;

    m_PSIFirstTexture.CreateFromImage(holoIniFile.GetPSIFirstImage());
    m_PSISecondTexture.CreateFromImage(holoIniFile.GetPSISecondImage());
    m_PSIThirdTexture.CreateFromImage(holoIniFile.GetPSIThirdImage());
    m_PSIFourthTexture.CreateFromImage(holoIniFile.GetPSIFourthImage());

    m_AmplitudeTexture.Create(128, 128); //CreateFromImage(holoIniFile.GetDoubleFFT128x128ImageFile());
    m_PhaseTexture.Create(128, 128);

    m_RenderProgram.LinkVertexShader(holoIniFile.GetVertexShaderFilePath());
    m_RenderProgram.LinkFragmentShader(holoIniFile.GetFragmentShaderFilePath());

    m_PSITransform.Init(holoIniFile.GetPSITransformComputeShaderFilePath());

    m_PSITransform.SetFirstPSIImage(m_PSIFirstTexture.GetTextureID());
    m_PSITransform.SetSecondPSIImage(m_PSISecondTexture.GetTextureID());
    m_PSITransform.SetThirdPSIImage(m_PSIThirdTexture.GetTextureID());
    m_PSITransform.SetFourthPSIImage(m_PSIFourthTexture.GetTextureID());
    m_PSITransform.SetAmplitudeImage(m_AmplitudeTexture.GetTextureID());
    m_PSITransform.SetPhaseImage(m_PhaseTexture.GetTextureID());

    m_FFTTransform.Init(holoIniFile.GetDoubleFFT128x128ComputeShaderFilePath());
    m_FFTTransform.SetAmplitudeTextureID(m_AmplitudeTexture.GetTextureID());
    m_FFTTransform.SetPhaseTextureID(m_PhaseTexture.GetTextureID());


    return true;
}

bool rctx::OpenGLFresnelScene::Calculate()
{
    m_PSITransform.Execute();

    auto executiontime = m_PSITransform.GetElapsedTime();

    double res = static_cast<double>(executiontime) / static_cast<double>(M_10E9);

    std::cout << "Execution time = " << res << " in seconds" << std::endl;

    return true;
}

bool rctx::OpenGLFresnelScene::Draw()
{
    glEnable(GL_TEXTURE_2D);

    m_RenderProgram.UseProgram();

    auto draw = [=](GLenum textureNum, GLuint textureID, int uniform, VertexArrayObject<float>& vao)
    {
        glActiveTexture(textureNum);
        glBindTexture(GL_TEXTURE_2D, textureID);
        m_RenderProgram.SetUniform1i("u_Texture", uniform);

        vao.Bind();
        vao.EnableArray(0);
        glDrawArrays(GL_QUADS, 0, 4);
        vao.DisableArray(0);
        vao.UnBind();

        glBindTexture(GL_TEXTURE_2D, 0);
    };

    draw(GL_TEXTURE0, m_AmplitudeTexture.GetTextureID(), 0, m_VAOAmplitude);
    draw(GL_TEXTURE1, m_PhaseTexture.GetTextureID(), 1, m_VAOPhase);

    glDisable(GL_TEXTURE_2D);

    return true;
}

bool rctx::OpenGLFresnelScene::Close()
{
    return true;
}

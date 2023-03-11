#pragma once

#include "IOpenGLTransform.h"
#include <render/opengl/shaders/Shader.h>
#include <render/opengl/shaders/GPUProgram.h>
#include <render/opengl/buffers/VertexBufferObjectClass.h>
#include <render/opengl/buffers/VertexArrayObject.h>

#include <iostream>
#include <vector>

namespace rctx
{
	class OpenGLPSITransform : public IOpenGLTransform
	{
	public:
		OpenGLPSITransform() = default;
		OpenGLPSITransform(const std::filesystem::path&);
		~OpenGLPSITransform() = default;

		void SetFirstPSIImage(GLuint);
		void SetSecondPSIImage(GLuint);
		void SetThirdPSIImage(GLuint);
		void SetFourthPSIImage(GLuint);
		void SetAmplitudeImage(GLuint);
		void SetPhaseImage(GLuint);

		void SetPhaseOne(float);
		void SetPhaseTwo(float);
		void SetPhaseThree(float);
		void SetPhaseFour(float);

		virtual void Init(const std::filesystem::path&) override;
		virtual void Execute() override;

	private:
		GPUProgram m_PSIProgram;

		std::filesystem::path m_SrcPath;

		GLuint m_FirstPSIImage;
		GLuint m_SecondPSIImage;
		GLuint m_ThirdPSIImage;
		GLuint m_FourthPSIImage;
		GLuint m_AmpltudeImage;
		GLuint m_PhaseImage;
		
		float m_PhaseOne;
		float m_PhaseTwo;
		float m_PhaseThree;
		float m_PhaseFour;
	};
}

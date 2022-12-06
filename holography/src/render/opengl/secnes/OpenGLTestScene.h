#pragma once

#include <GL/glew.h>
#include <render/opengl/OpenGLTexture.h>
#include <render/opengl/secnes/IOpenGLScene.h>
#include <share/HoloIniFileController.h>
#include <gui/Color.h>

namespace rctx
{
	class OpenGLTestScene : public IOpenGLScene
	{
	public:
		OpenGLTestScene() = default;
		~OpenGLTestScene() = default;

		virtual bool Load() override;
		virtual bool Calculate() override;
		virtual bool Draw() override;
		virtual bool Close() override;

	private:
		OpenGLTexture m_PSIFirstTexture;
		OpenGLTexture m_PSISecondTexture;
		OpenGLTexture m_PSIThirdTexture;
		OpenGLTexture m_PSIFourthTexture;

		gui::Color white;
	};
}

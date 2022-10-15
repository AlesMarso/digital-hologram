#pragma once

#include <share/IniFileController.h>

namespace share
{
	class HoloIniFileController
	{
	public:
		HoloIniFileController();
		~HoloIniFileController() = default;

		std::string GetImageName() const;
		std::filesystem::path GetImageFileName() const;

		std::filesystem::path GetPSIFirstImage() const;
		std::filesystem::path GetPSISecondImage() const;
		std::filesystem::path GetPSIThirdImage() const;
		std::filesystem::path GetPSIFourthImage() const;
		std::filesystem::path GetVertexShaderFilePath() const;
		std::filesystem::path GetFragmentShaderFilePath() const;

	private:
		std::string m_HoloIniFileName;
		std::string m_TestImageSection;

		std::string m_PSIFirstImage_SectionName;
		std::string m_PSISecondImage_SectionName;
		std::string m_PSIThirdImage_SectionName;
		std::string m_PSIFourthImage_SectionName;
		std::string m_VertexShader_SectionName;
		std::string m_FragmentShader_SectionName;

		std::string m_ImageFileKey;
		std::string m_FilePathKey;
	};
}

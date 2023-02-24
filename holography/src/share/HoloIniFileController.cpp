#include "HoloIniFileController.h"

share::HoloIniFileController::HoloIniFileController()
	: m_HoloIniFileName("holo.ini"),
	m_TestImageSection("Testimage"),
	m_ImageFileKey("ImageFile"),
	m_FilePathKey("FilePath"),
	m_PSIFirstImage_SectionName("PSI_Image_First"),
	m_PSISecondImage_SectionName("PSI_Image_Second"),
	m_PSIThirdImage_SectionName("PSI_Image_Third"),
	m_PSIFourthImage_SectionName("PSI_Image_Fourth"),
	m_VertexShader_SectionName("Vertex_Shader"),
	m_FragmentShader_SectionName("Fragment_Shader"),
	m_ComputeShader_SectionName("Compute_Shader"),
	m_DoubleFFT128x128_SectionName("DoubleFFT128x128")
{
	IniFileController::getInstance()->SetIniFileName(m_HoloIniFileName);
}

std::string share::HoloIniFileController::GetImageName() const
{
	return IniFileController::getInstance()->GetString(m_TestImageSection, m_ImageFileKey);
}

std::filesystem::path share::HoloIniFileController::GetImageFileName() const
{
	return IniFileController::getInstance()->GetFullFilePath(m_TestImageSection, m_ImageFileKey);
}

std::filesystem::path share::HoloIniFileController::GetPSIFirstImage() const
{
	return IniFileController::getInstance()->GetFullFilePath(m_PSIFirstImage_SectionName, m_ImageFileKey);
}

std::filesystem::path share::HoloIniFileController::GetPSISecondImage() const
{
	return IniFileController::getInstance()->GetFullFilePath(m_PSISecondImage_SectionName, m_ImageFileKey);
}

std::filesystem::path share::HoloIniFileController::GetPSIThirdImage() const
{
	return IniFileController::getInstance()->GetFullFilePath(m_PSIThirdImage_SectionName, m_ImageFileKey);
}

std::filesystem::path share::HoloIniFileController::GetPSIFourthImage() const
{
	return IniFileController::getInstance()->GetFullFilePath(m_PSIFourthImage_SectionName, m_ImageFileKey);
}

std::filesystem::path share::HoloIniFileController::GetVertexShaderFilePath() const
{
	return IniFileController::getInstance()->GetFullFilePath(m_VertexShader_SectionName, m_FilePathKey);
}

std::filesystem::path share::HoloIniFileController::GetFragmentShaderFilePath() const
{
	return IniFileController::getInstance()->GetFullFilePath(m_FragmentShader_SectionName, m_FilePathKey);
}

std::filesystem::path share::HoloIniFileController::GetComputeShaderFilePath() const
{
	return IniFileController::getInstance()->GetFullFilePath(m_ComputeShader_SectionName, m_FilePathKey);
}

std::filesystem::path share::HoloIniFileController::GetDoubleFFT128x128ImageFile() const
{
	return IniFileController::getInstance()->GetFullFilePath(m_DoubleFFT128x128_SectionName, m_ImageFileKey);
}

std::filesystem::path share::HoloIniFileController::GetDoubleFFT128x128ComputeShaderFilePath() const
{
	return IniFileController::getInstance()->GetFullFilePath(m_DoubleFFT128x128_SectionName, m_FilePathKey);
}

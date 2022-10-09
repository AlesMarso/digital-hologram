#include "HoloIniFileController.h"

share::HoloIniFileController::HoloIniFileController()
	: m_HoloIniFileName("holo.ini"),
	m_TestImageSection("Testimage"),
	m_ImageFileKey("ImageFile"),
	m_PSIFirstImage_SectionName("PSI_Image_First"),
	m_PSISecondImage_SectionName("PSI_Image_Second"),
	m_PSIThirdImage_SectionName("PSI_Image_Third"),
	m_PSIFourthImage_SectionName("PSI_Image_Fourth")
{
	IniFileController::getInstance()->SetIniFileName(m_HoloIniFileName);
}

std::string share::HoloIniFileController::GetImageName() const
{
	return IniFileController::getInstance()->GetString(m_TestImageSection, m_ImageFileKey);
}

std::filesystem::path share::HoloIniFileController::GetImageFileName() const
{
	std::string m_ImgFileName = GetImageName();

	string1024 executableFileName = { 0 };

	GetModuleFileName(nullptr, executableFileName, 1024);

	std::filesystem::path execDirPath = std::filesystem::path(executableFileName).remove_filename();
	execDirPath.append(m_ImgFileName);

	return execDirPath;
}

std::filesystem::path share::HoloIniFileController::GetPSIFirstImage() const
{
	std::string m_ImgFileName = IniFileController::getInstance()->GetString(m_PSIFirstImage_SectionName, m_ImageFileKey);

	string1024 executableFileName = { 0 };

	GetModuleFileName(nullptr, executableFileName, 1024);

	std::filesystem::path execDirPath = std::filesystem::path(executableFileName).remove_filename();
	execDirPath.append(m_ImgFileName);

	return execDirPath;
}

std::filesystem::path share::HoloIniFileController::GetPSISecondImage() const
{
	std::string m_ImgFileName = IniFileController::getInstance()->GetString(m_PSISecondImage_SectionName, m_ImageFileKey);

	string1024 executableFileName = { 0 };

	GetModuleFileName(nullptr, executableFileName, 1024);

	std::filesystem::path execDirPath = std::filesystem::path(executableFileName).remove_filename();
	execDirPath.append(m_ImgFileName);

	return execDirPath;
}

std::filesystem::path share::HoloIniFileController::GetPSIThirdImage() const
{
	std::string m_ImgFileName = IniFileController::getInstance()->GetString(m_PSIThirdImage_SectionName, m_ImageFileKey);

	string1024 executableFileName = { 0 };

	GetModuleFileName(nullptr, executableFileName, 1024);

	std::filesystem::path execDirPath = std::filesystem::path(executableFileName).remove_filename();
	execDirPath.append(m_ImgFileName);

	return execDirPath;
}

std::filesystem::path share::HoloIniFileController::GetPSIFourthImage() const
{
	std::string m_ImgFileName = IniFileController::getInstance()->GetString(m_PSIFourthImage_SectionName, m_ImageFileKey);

	string1024 executableFileName = { 0 };

	GetModuleFileName(nullptr, executableFileName, 1024);

	std::filesystem::path execDirPath = std::filesystem::path(executableFileName).remove_filename();
	execDirPath.append(m_ImgFileName);

	return execDirPath;
}

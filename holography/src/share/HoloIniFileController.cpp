#include "HoloIniFileController.h"

share::HoloIniFileController::HoloIniFileController()
	: m_HoloIniFileName("holo.ini"),
	m_TestImageSection("Testimage"),
	m_ImageFileKey("ImageFile")
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

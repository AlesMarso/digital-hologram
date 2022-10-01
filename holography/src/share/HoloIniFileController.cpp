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

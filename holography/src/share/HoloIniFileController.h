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
		std::string GetImageFileName() const;

	private:
		std::string m_HoloIniFileName;
		std::string m_TestImageSection;
		std::string m_ImageFileKey;
	};
}

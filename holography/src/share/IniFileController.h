#pragma once

#include <windows.h>
#include <filesystem>

#include <share/types.h>

namespace share
{
	class IniFileController
	{
	public:
		IniFileController();
		~IniFileController();

		void SetIniFileName(std::string);
		std::string GetString(std::string, std::string);

	private:
		std::filesystem::path m_IniFilePath;
		std::filesystem::path m_CurrentExecutableDirectoryPath;

	public:
		static IniFileController* getInstance();
		static void deleteInstance();

	private:
		static IniFileController* m_pInstance;
	};
}

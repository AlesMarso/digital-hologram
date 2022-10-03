#include "IniFileController.h"

namespace share
{
    IniFileController* IniFileController::m_pInstance = nullptr;

    IniFileController::IniFileController()
    {
        string1024 executableFileName = { 0 };

        GetModuleFileName(nullptr, executableFileName, 1024);

        m_CurrentExecutableDirectoryPath = std::filesystem::path(executableFileName).remove_filename();
    }

    IniFileController::~IniFileController()
    {
    }

    void IniFileController::SetIniFileName(std::string iniFileName)
    {
        m_IniFilePath = m_CurrentExecutableDirectoryPath;
        m_IniFilePath.append(iniFileName);
    }

    std::string IniFileController::GetString(std::string section, std::string key)
    {
        string1024 keyValue = { 0 };

        GetPrivateProfileString(section.c_str(), key.c_str(), "", keyValue, 1024, m_IniFilePath.string().data());

        return std::string(keyValue);
    }

    IniFileController* IniFileController::getInstance()
    {
        if (!m_pInstance)
            m_pInstance = new IniFileController();

        return m_pInstance;
    }

    void IniFileController::deleteInstance()
    {
        if (!m_pInstance)
            delete m_pInstance;
    }
}
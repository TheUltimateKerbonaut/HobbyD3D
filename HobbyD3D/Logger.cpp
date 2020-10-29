#include "pch.h"
#include "Logger.h"
#include "StringConverter.h"

void Logger::Log(const std::string& sMessage)
{
	const std::string sDisplayMessage = "Error: " + sMessage;
	MessageBoxA(NULL, sDisplayMessage.c_str(), "Eror", MB_ICONERROR);
}

void Logger::Log(HRESULT hr, const std::string& sMessage)
{
	_com_error error(hr);
	std::wstring sDisplayMessage = L"Error: " + StringConverter::StringToWide(sMessage) + L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, sDisplayMessage.c_str(), L"Error", MB_ICONERROR);
}

void Logger::Log(HRESULT hr, const std::wstring& sMessage)
{
	_com_error error(hr);
	std::wstring sDisplayMessage = L"Error: " + sMessage + L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, sDisplayMessage.c_str(), L"Error", MB_ICONERROR);
}


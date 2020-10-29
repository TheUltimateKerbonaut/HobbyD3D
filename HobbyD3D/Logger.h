#pragma once

#include "pch.h"

class Logger
{
public:
	static void Log(const std::string& sMessage);
	static void Log(HRESULT hr, const std::string& sMessage);
	static void Log(HRESULT hr, const std::wstring& sMessage);
};


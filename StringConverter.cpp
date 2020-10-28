#include "pch.h"
#include "StringConverter.h"

std::wstring StringConverter::StringToWide(const std::string& sString)
{
	return std::wstring(sString.begin(), sString.end());
}

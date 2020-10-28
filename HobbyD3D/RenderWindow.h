#pragma once
#include "pch.h"
#include "StringConverter.h"

class RenderWindow
{
public:
	RenderWindow(HINSTANCE instance, unsigned int nWidth, unsigned int nHeight);
	~RenderWindow();

	BOOL GetMessages();
	void Update();

	inline WPARAM GetExitStatus() { return m_Msg.wParam; }

private:
	void RegisterWindowClass();
	void CreateWindowInstance();

	HINSTANCE	m_Instance;
	WNDCLASSEX	m_WindowClass;
	HWND		m_Window;
	MSG			m_Msg;

	const std::wstring m_pClassName =	StringConverter::StringToWide("HobbyD3D");
	const std::wstring m_pWindowName =	StringConverter::StringToWide("HobbyD3D");

	unsigned int m_Width;
	unsigned int m_Height;
};


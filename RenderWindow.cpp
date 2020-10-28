#include "pch.h"
#include "RenderWindow.h"

RenderWindow::RenderWindow(HINSTANCE instance, unsigned int width, unsigned int height)
{
	m_Instance = instance;
	m_Width = width;
	m_Height = height;

	RegisterWindowClass();
	CreateWindowInstance();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		break;
		
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void RenderWindow::RegisterWindowClass()
{
	m_WindowClass = { 0 };
	m_WindowClass.cbSize =			sizeof(WNDCLASSEX);
	m_WindowClass.style =			CS_OWNDC;
	m_WindowClass.lpfnWndProc =		WndProc;
	m_WindowClass.cbClsExtra =		0;
	m_WindowClass.cbWndExtra =		0;
	m_WindowClass.hInstance =		m_Instance;
	m_WindowClass.hIcon =			nullptr;
	m_WindowClass.hCursor =			nullptr;
	m_WindowClass.hbrBackground =	nullptr;
	m_WindowClass.lpszMenuName =	nullptr;
	m_WindowClass.lpszClassName =	m_pClassName.c_str();
	m_WindowClass.hIconSm =			nullptr;

	RegisterClassEx(&m_WindowClass);
}

void RenderWindow::CreateWindowInstance()
{
	// Get screen width and height first, to centre screen
	int nScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - m_Height / 2;
	int nScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - m_Width / 2;

	// Create window
	m_Window = CreateWindowEx(
		0, 
		m_pClassName.c_str(),
		m_pWindowName.c_str(),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		nScreenX,
		nScreenX,
		m_Width,
		m_Height,
		nullptr,
		nullptr,
		m_Instance,
		nullptr
	);

	// Show window
	ShowWindow(m_Window, SW_SHOW);
}

BOOL RenderWindow::GetMessages()
{
	// If less than 1, close
	return GetMessage(&m_Msg, nullptr, 0, 0) > 0;
}

void RenderWindow::Update()
{
	TranslateMessage(&m_Msg);
	DispatchMessage(&m_Msg);
}

RenderWindow::~RenderWindow()
{
	DestroyWindow(m_Window);
}
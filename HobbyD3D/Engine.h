#pragma once
#include "RenderWindow.h"

class Engine
{
public:
	Engine(HINSTANCE instance);
	~Engine();

	BOOL Update();
	void Prepare();
	int GetExitStatus();

private:
	RenderWindow m_Window;
};


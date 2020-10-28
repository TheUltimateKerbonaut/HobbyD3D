#pragma once
#include "RenderWindow.h"
#include "Graphics/Renderer.h"

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
	Renderer m_Renderer;
};


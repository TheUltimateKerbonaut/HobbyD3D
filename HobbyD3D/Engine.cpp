#include "pch.h"
#include "Engine.h"

Engine::Engine(HINSTANCE instance) : m_Window(instance, 800, 600)
{

}

BOOL Engine::Update()
{
	return m_Window.GetMessages();
}

void Engine::Prepare()
{
	m_Window.Update();
}

int Engine::GetExitStatus()
{
	return static_cast<int>(m_Window.GetExitStatus());
}

Engine::~Engine()
{

}

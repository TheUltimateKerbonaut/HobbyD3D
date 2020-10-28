#include "pch.h"
#include "Engine.h"

constexpr unsigned int width =	800;
constexpr unsigned int height = 600;

Engine::Engine(HINSTANCE instance) : m_Window(instance, width, height), m_Renderer(m_Window)
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

void Engine::Render()
{
	m_Renderer.RenderFrame();
}

int Engine::GetExitStatus()
{
	return static_cast<int>(m_Window.GetExitStatus());
}

Engine::~Engine()
{

}

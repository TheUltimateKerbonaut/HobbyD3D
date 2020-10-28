#include "pch.h"
#include "Renderer.h"

Renderer::Renderer()
{
	InitDirectX();
}

void Renderer::InitDirectX()
{
	Adapter adapter = AdapterList().ChoseAdapter();
}

Renderer::~Renderer()
{

}

#pragma once
#include "pch.h"
#include "AdapterList.h"
#include "../RenderWindow.h"
#include "Shaders.h"

using Microsoft::WRL::ComPtr;

class Renderer
{
public:
	Renderer(RenderWindow& window);
	~Renderer();

	void RenderFrame();

private:

	bool InitDirectX(RenderWindow& window);
	bool InitShaders();

	bool CreateDeviceAndSwapchain(RenderWindow& window);
	bool CreateRenderTargetView();

	ComPtr<ID3D11Device>			m_Device;
	ComPtr<ID3D11DeviceContext>		m_DeviceContext;
	ComPtr<IDXGISwapChain>			m_Swapchain;
	ComPtr<ID3D11RenderTargetView>	m_RenderTargetView;

	ComPtr<ID3D11InputLayout>		m_InputLayout;

	VertexShader m_VertexShader;
};


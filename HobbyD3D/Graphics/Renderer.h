#pragma once
#include "pch.h"
#include "AdapterList.h"
#include "../RenderWindow.h"

using Microsoft::WRL::ComPtr;

class Renderer
{
public:
	Renderer(RenderWindow& window);
	~Renderer();

	void RenderFrame();

private:

	void InitDirectX(RenderWindow& window);

	void CreateDeviceAndSwapchain(RenderWindow& window);
	void CreateRenderTargetView();

	ComPtr<ID3D11Device>			m_Device;
	ComPtr<ID3D11DeviceContext>		m_DeviceContext;
	ComPtr<IDXGISwapChain>			m_Swapchain;
	ComPtr<ID3D11RenderTargetView>	m_RenderTargetView;

};


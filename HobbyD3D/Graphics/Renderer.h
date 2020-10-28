#pragma once
#include "pch.h"
#include "AdapterList.h"

using Microsoft::WRL::ComPtr;

class Renderer
{
public:
	Renderer();
	~Renderer();

private:

	void InitDirectX();

	ComPtr<ID3D11Device>			m_Device;
	ComPtr<ID3D11DeviceContext>		m_DeviceContext;
	ComPtr<IDXGISwapChain>			m_Swapchain;
	ComPtr<ID3D11RenderTargetView>	m_RenderTargetView;

};


#pragma once
#include "pch.h"
#include "AdapterList.h"
#include "../RenderWindow.h"
#include "Shaders.h"
#include "Vertex.h"

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
	bool InitScene();

	bool CreateDeviceAndSwapchain(RenderWindow& window);
	bool CreateRenderTargetView(RenderWindow& window);

	ComPtr<ID3D11Device>			m_Device;
	ComPtr<ID3D11DeviceContext>		m_DeviceContext;
	ComPtr<IDXGISwapChain>			m_Swapchain;
	ComPtr<ID3D11RenderTargetView>	m_RenderTargetView;
	ComPtr<ID3D11RasterizerState>	m_RasterizerState;

	VertexShader	m_VertexShader;
	PixelShader		m_PixelShader;

	ComPtr<ID3D11Buffer>	m_VertexBuffer;

};


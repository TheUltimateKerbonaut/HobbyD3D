#include "pch.h"
#include "Renderer.h"
#include "../Logger.h"

Renderer::Renderer(RenderWindow& window)
{
	InitDirectX(window);
}

void Renderer::InitDirectX(RenderWindow& window)
{
	CreateDeviceAndSwapchain(window);
	CreateRenderTargetView();
}

void Renderer::CreateDeviceAndSwapchain(RenderWindow& window)
{
	// Choose adapter
	Adapter adapter = AdapterList().ChoseAdapter();

	// Create swapchain description
	DXGI_SWAP_CHAIN_DESC swapchainDescription = { 0 };

	// Display mode
	swapchainDescription.BufferDesc.Width = window.GetWidth();
	swapchainDescription.BufferDesc.Height = window.GetHeight();
	swapchainDescription.BufferDesc.RefreshRate.Numerator = 60; // TODO: Query correct refresh rate
	swapchainDescription.BufferDesc.RefreshRate.Denominator = 1;
	swapchainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapchainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Multisampling
	swapchainDescription.SampleDesc.Count = 1;
	swapchainDescription.SampleDesc.Quality = 0;

	// Buffer usage
	swapchainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDescription.BufferCount = 1;
	swapchainDescription.OutputWindow = window.GetWindow();
	swapchainDescription.Windowed = TRUE;
	swapchainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapchainDescription.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // Allow swapping between fullscreen and windowed

	// Create device and swapchain
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		adapter.pAdapter,			// IDXGI adapter
		D3D_DRIVER_TYPE_UNKNOWN,	// Driver type
		NULL,						// For software driver type
		NULL,						// Flags for runtime layers
		NULL,						// Freature levels array
		0,							// Number of features in levels array
		D3D11_SDK_VERSION,			// SDK version
		&swapchainDescription,		// Swapchain description
		m_Swapchain.GetAddressOf(),	// Swapchain
		m_Device.GetAddressOf(),	// Device
		NULL,						// Supported feature length
		m_DeviceContext.GetAddressOf()
	);

	if (FAILED(hr))
	{
		Logger::Log(hr, "Failed to create D3D11 device and swapchain.");
		exit(-1);
	}
}

void Renderer::CreateRenderTargetView()
{
	// Get backbuffer from swapchain
	ComPtr<ID3D11Texture2D> backBuffer;
	HRESULT hr = m_Swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
	if (FAILED(hr))
	{
		Logger::Log(hr, "Failed to get backbuffer from swapchain");
		exit(-1);
	}

	hr = m_Device->CreateRenderTargetView(backBuffer.Get(), NULL, m_RenderTargetView.GetAddressOf());
	if (FAILED(hr))
	{
		Logger::Log(hr, "Failed to create render target view");
		exit(-1);
	}
	
	// Set render target
	m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), NULL); // Last argument - pointer to render stencil view
}

void Renderer::RenderFrame()
{
	float bgColour[] = { 0.2f, 0.3f, 0.3f, 1.0f };

	// Clear render target view
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), bgColour);

	// Present swapchain
	m_Swapchain->Present(1, NULL); // Vsync, flags
}

Renderer::~Renderer()
{

}

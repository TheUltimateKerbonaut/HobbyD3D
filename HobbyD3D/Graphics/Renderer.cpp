#include "pch.h"
#include "Renderer.h"
#include "../Logger.h"

Renderer::Renderer(RenderWindow& window)
{
	InitDirectX(window);
	InitShaders();
}

bool Renderer::InitDirectX(RenderWindow& window)
{
	if (!CreateDeviceAndSwapchain(window)) return false;
	if (!CreateRenderTargetView()) return false;
	return true;
}

bool Renderer::CreateDeviceAndSwapchain(RenderWindow& window)
{
	// Choose adapter
	AdapterList list = AdapterList();
	if (!list.Init()) return false;
	Adapter adapter = list.ChoseAdapter();

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
		return false;
	}

	return true;
}

bool Renderer::CreateRenderTargetView()
{
	// Get backbuffer from swapchain
	ComPtr<ID3D11Texture2D> backBuffer;
	HRESULT hr = m_Swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
	if (FAILED(hr))
	{
		Logger::Log(hr, "Failed to get backbuffer from swapchain");
		return false;
	}

	hr = m_Device->CreateRenderTargetView(backBuffer.Get(), NULL, m_RenderTargetView.GetAddressOf());
	if (FAILED(hr))
	{
		Logger::Log(hr, "Failed to create render target view");
		return false;
	}
	
	// Set render target
	m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), NULL); // Last argument - pointer to render stencil view

	return true;
}

void Renderer::RenderFrame()
{
	float bgColour[] = { 0.2f, 0.3f, 0.3f, 1.0f };

	// Clear render target view
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), bgColour);

	// Present swapchain
	m_Swapchain->Present(1, NULL); // Vsync, flags
}

bool Renderer::InitShaders()
{
	// Determine shader path
	std::wstring sShaderFolder = L"";
#pragma region GetShaderPath
	if (IsDebuggerPresent() == TRUE)
	{
#ifdef _DEBUG
	#ifdef _WIN64
		sShaderFolder = L"../x64/Debug/";
	#else
		sShaderFolder = L"../Debug/";
	#endif
#else
	#ifdef _WIN64
			sShaderFolder = L"../x64/Release/";
	#else
			sShaderFolder = L"../Release/";
	#endif
#endif
	}

	if (!m_VertexShader.Init(m_Device, sShaderFolder + L"VertexShader.cso")) return false;

	std::array<D3D11_INPUT_ELEMENT_DESC, 1> layout =
	{
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	HRESULT hr = m_Device->CreateInputLayout(
		layout.data(), 
		(UINT) layout.size(), 
		m_VertexShader.GetBuffer()->GetBufferPointer(),
		m_VertexShader.GetBuffer()->GetBufferSize(),
		m_InputLayout.GetAddressOf()
	);

	if (FAILED(hr))
	{
		Logger::Log(hr, "Failed to create input layout.");
		return false;
	}

	return true;
}

Renderer::~Renderer()
{
	
}

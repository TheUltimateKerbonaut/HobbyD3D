#include "pch.h"
#include "Renderer.h"
#include "../Logger.h"

Renderer::Renderer(RenderWindow& window)
{
	InitDirectX(window);
	InitShaders();
	InitScene();
}

bool Renderer::InitDirectX(RenderWindow& window)
{
	if (!CreateDeviceAndSwapchain(window)) return false;
	if (!CreateRenderTargetView(window)) return false;
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

bool Renderer::CreateRenderTargetView(RenderWindow& window)
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

	// Create the viewport
	D3D11_VIEWPORT viewport = { 0 };
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(window.GetWidth());
	viewport.Height = static_cast<float>(window.GetHeight());

	// Set the viewport
	m_DeviceContext->RSSetViewports(1, &viewport);

	return true;
}

void Renderer::RenderFrame()
{
	// Clear render target view
	float bgColour[] = { 0.2f, 0.3f, 0.3f, 1.0f };
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), bgColour);

	m_DeviceContext->IASetInputLayout(m_VertexShader.GetInputLayout());
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_DeviceContext->VSSetShader(m_VertexShader.GetShader(), NULL, 0);
	m_DeviceContext->PSSetShader(m_PixelShader.GetShader(), NULL, 0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_DeviceContext->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);

	m_DeviceContext->Draw(3, 0);

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

	std::vector<D3D11_INPUT_ELEMENT_DESC> layout =
	{
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOUR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	if (!m_VertexShader.Init(m_Device, sShaderFolder + L"VertexShader.cso", layout)) return false;
	if (!m_PixelShader.Init(m_Device, sShaderFolder + L"PixelShader.cso", layout)) return false;

	return true;
}

bool Renderer::InitScene()
{
	std::vector<Vertex> vertices =
	{
		{ -0.5f, -0.5f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.5f, 0.0f, 1.0f, 0.0f },
		{ 0.5f, -0.5f, 0.0f, 0.0f, 1.0f }
	};

	D3D11_BUFFER_DESC vertexBufferDescription = { 0 };
	vertexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDescription.ByteWidth = static_cast<UINT>(sizeof(Vertex) * vertices.size());
	vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDescription.CPUAccessFlags = 0;
	vertexBufferDescription.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.pSysMem = vertices.data();

	HRESULT hr = m_Device->CreateBuffer(&vertexBufferDescription, &vertexBufferData, m_VertexBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		Logger::Log(hr, "Failed to create vertex buffer.");
		return false;
	}

	return true;
}

Renderer::~Renderer()
{
	
}

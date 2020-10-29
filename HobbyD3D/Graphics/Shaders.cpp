#include "pch.h"
#include "Shaders.h"
#include "../Logger.h"

VertexShader::VertexShader() {}

bool VertexShader::Init(ComPtr<ID3D11Device>& device, const std::wstring& sFilename, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout)
{
	// Read file
	HRESULT hr = D3DReadFileToBlob(sFilename.c_str(), m_Buffer.GetAddressOf());
	if (FAILED(hr))
	{
		Logger::Log(hr, L"Failed to load shader " + sFilename);
		return false;
	}

	// Create shader
	hr = device->CreateVertexShader(m_Buffer->GetBufferPointer(), m_Buffer->GetBufferSize(), NULL, m_Shader.GetAddressOf());
	if (FAILED(hr))
	{
		Logger::Log(hr, L"Failed to create vertex shader " + sFilename);
		return false;
	}

	// Create input layout
	hr = device->CreateInputLayout(
		layout.data(),
		(UINT)layout.size(),
		GetBuffer()->GetBufferPointer(),
		GetBuffer()->GetBufferSize(),
		m_InputLayout.GetAddressOf()
	);
	if (FAILED(hr))
	{
		Logger::Log(hr, "Failed to create input layout.");
		return false;
	}

	return true;
}

ID3D11VertexShader* VertexShader::GetShader()	{ return m_Shader.Get(); }
ID3D10Blob* VertexShader::GetBuffer()			{ return m_Buffer.Get(); }

VertexShader::~VertexShader() {}

PixelShader::PixelShader() {}

bool PixelShader::Init(ComPtr<ID3D11Device>& device, const std::wstring& sFilename, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout)
{
	// Read file
	HRESULT hr = D3DReadFileToBlob(sFilename.c_str(), m_Buffer.GetAddressOf());
	if (FAILED(hr))
	{
		Logger::Log(hr, L"Failed to load shader " + sFilename);
		return false;
	}

	// Create shader
	hr = device->CreatePixelShader(m_Buffer->GetBufferPointer(), m_Buffer->GetBufferSize(), NULL, m_Shader.GetAddressOf());
	if (FAILED(hr))
	{
		Logger::Log(hr, L"Failed to create vertex shader " + sFilename);
		return false;
	}

	// Create input layout
	hr = device->CreateInputLayout(
		layout.data(),
		(UINT)layout.size(),
		GetBuffer()->GetBufferPointer(),
		GetBuffer()->GetBufferSize(),
		m_InputLayout.GetAddressOf()
	);
	if (FAILED(hr))
	{
		Logger::Log(hr, "Failed to create input layout.");
		return false;
	}

	return true;
}

ID3D11PixelShader* PixelShader::GetShader() { return m_Shader.Get(); }
ID3D10Blob* PixelShader::GetBuffer() { return m_Buffer.Get(); }

PixelShader::~PixelShader() {}

#include "pch.h"
#include "Shaders.h"
#include "../Logger.h"

VertexShader::VertexShader() {}

bool VertexShader::Init(ComPtr<ID3D11Device>& device, std::wstring sFilename)
{
	HRESULT hr = D3DReadFileToBlob(sFilename.c_str(), m_Buffer.GetAddressOf());
	if (FAILED(hr))
	{
		Logger::Log(hr, L"Failed to load shader " + sFilename);
		return false;
	}

	hr = device->CreateVertexShader(m_Buffer->GetBufferPointer(), m_Buffer->GetBufferSize(), NULL, m_Shader.GetAddressOf());
	if (FAILED(hr))
	{
		Logger::Log(hr, L"Failed to create vertex shader " + sFilename);
		return false;
	}

	return true;
}

ID3D11VertexShader* VertexShader::GetShader()	{ return m_Shader.Get(); }
ID3D10Blob* VertexShader::GetBuffer()			{ return m_Buffer.Get(); }

VertexShader::~VertexShader() {}

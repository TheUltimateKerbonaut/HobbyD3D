#pragma once
#include "pch.h"

using Microsoft::WRL::ComPtr;

class VertexShader
{
public:
	VertexShader();
	~VertexShader();

	bool Init(ComPtr<ID3D11Device>& device, const std::wstring& sFilename, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout);

	ID3D11VertexShader* GetShader();
	ID3D10Blob*			GetBuffer();

private:
	ComPtr<ID3D11VertexShader>	m_Shader;
	ComPtr<ID3D10Blob>			m_Buffer;
	ComPtr<ID3D11InputLayout>	m_InputLayout;

};

class PixelShader
{
public:
	PixelShader();
	~PixelShader();

	bool Init(ComPtr<ID3D11Device>& device, const std::wstring& sFilename, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout);

	ID3D11PixelShader* GetShader();
	ID3D10Blob* GetBuffer();

private:
	ComPtr<ID3D11PixelShader>	m_Shader;
	ComPtr<ID3D10Blob>			m_Buffer;
	ComPtr<ID3D11InputLayout>	m_InputLayout;

};
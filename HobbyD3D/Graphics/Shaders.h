#pragma once
#include "pch.h"

using Microsoft::WRL::ComPtr;

class VertexShader
{
public:
	VertexShader();
	~VertexShader();

	bool Init(ComPtr<ID3D11Device>& device, std::wstring sFilename);

	ID3D11VertexShader* GetShader();
	ID3D10Blob*			GetBuffer();

private:
	ComPtr<ID3D11VertexShader>	m_Shader;
	ComPtr<ID3D10Blob>			m_Buffer;

};
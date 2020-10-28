#include "pch.h"
#include "AdapterList.h"
#include "../Logger.h"

using Microsoft::WRL::ComPtr;

AdapterList::AdapterList()
{
	// Create a IDXGIFactory
	ComPtr<IDXGIFactory> pFactory;
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));
	if (FAILED(hr))
	{
		Logger::Log(hr, "Failed to create IDXGIFactory factory for enumerating adapters.");
		exit(-1);
	}

	// Enum adapters
	unsigned int i = 0;
	IDXGIAdapter* pAdapter;
	while (pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC pDescription;
		pAdapter->GetDesc(&pDescription);
		m_vAdapters.push_back({ pAdapter, pDescription });
		++i;
	}

	if (m_vAdapters.size() < 1)
	{
		Logger::Log("No IDXGI adapters found.");
		exit(-1);
	}
}

AdapterList::~AdapterList()
{
}

Adapter AdapterList::ChoseAdapter()
{
	// Pick the adapter with the most VRAM
	std::sort(std::begin(m_vAdapters), std::end(m_vAdapters), [](Adapter a, Adapter b)
	{
		return a.description.DedicatedVideoMemory > b.description.DedicatedVideoMemory;
	});

	return m_vAdapters.front();
}

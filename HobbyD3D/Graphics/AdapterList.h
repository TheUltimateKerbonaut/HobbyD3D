#pragma once
#include "pch.h"

struct Adapter
{
	IDXGIAdapter* pAdapter;
	DXGI_ADAPTER_DESC description;
};

class AdapterList
{
public:
	AdapterList();
	~AdapterList();

	Adapter ChoseAdapter();

private:
	std::vector<Adapter> m_vAdapters;
};


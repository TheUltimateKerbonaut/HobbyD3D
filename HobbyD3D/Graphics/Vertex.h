#pragma once
#include "pch.h"

struct Vertex
{
	Vertex() : pos(0.0f, 0.0f), colour(0.0f, 0.0f, 0.0f) {}
	Vertex(float x, float y, float r, float g, float b) : pos(x, y), colour(r, g, b) {}

	DirectX::XMFLOAT2 pos;
	DirectX::XMFLOAT3 colour;
};
#pragma once
#include "Graphics/BETexture.h"
#include "Graphics/Platforms/D3DX12/d3dx12Include.h"

class Texture final : public BETexture
{
public:
	Texture(ID3D12Resource*, D3D12_RESOURCE_STATES);
	~Texture() noexcept = default;

	size_t Size() const;
	uint32_t Width() const { return width; }
	uint32_t Height() const { return height; }
	BEPixelFormat Format() const { return format; }

	ID3D12Resource* Buffer() const { return buffer.Get(); }
	D3D12_RESOURCE_STATES InitialState() const { return initialState; }

private:
	uint32_t width;
	uint32_t height;
	BEPixelFormat format;

	ComPtr<ID3D12Resource> buffer;
	D3D12_RESOURCE_STATES initialState;
};
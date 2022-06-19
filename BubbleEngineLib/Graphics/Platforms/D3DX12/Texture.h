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

	ID3D12Resource* Resource() const { return resource.Get(); }
	D3D12_RESOURCE_STATES InitialState() const { return initialState; }

	void SetRenderTargetViewHeap(ID3D12DescriptorHeap* heap);
	void SetDepthStencilViewHeap(ID3D12DescriptorHeap* heap);
	void SetShaderResourceViewHeap(ID3D12DescriptorHeap* heap);

	D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetView() const;
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const;
	D3D12_CPU_DESCRIPTOR_HANDLE ShaderResourceView() const;

private:
	uint32_t width;
	uint32_t height;
	BEPixelFormat format;
	D3D12_RESOURCE_STATES initialState;

	ComPtr<ID3D12Resource> resource;
	ComPtr<ID3D12DescriptorHeap> renderTargetViewHeap;
	ComPtr<ID3D12DescriptorHeap> depthStencilViewHeap;
	ComPtr<ID3D12DescriptorHeap> shaderResourceViewHeap;

};
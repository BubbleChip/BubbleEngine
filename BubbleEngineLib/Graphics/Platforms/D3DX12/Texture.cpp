#include "Texture.h"

Texture::Texture(ID3D12Resource* _resource, D3D12_RESOURCE_STATES _initialState)
	: resource(_resource)
	, initialState(_initialState)
{
	D3D12_RESOURCE_DESC desc = resource->GetDesc();
	width = static_cast<uint32_t>(desc.Width);
	height = static_cast<uint32_t>(desc.Height);
	format = BEPixelFormat(desc.Format);
}

size_t Texture::Size() const
{
	return AlignTextureRowPitch(width * PixelFormatSize(format)) * height;
}

void Texture::SetRenderTargetViewHeap(ID3D12DescriptorHeap* heap)
{
	renderTargetViewHeap = heap;
}

void Texture::SetDepthStencilViewHeap(ID3D12DescriptorHeap* heap)
{
	depthStencilViewHeap = heap;
}

void Texture::SetShaderResourceViewHeap(ID3D12DescriptorHeap* heap)
{
	shaderResourceViewHeap = heap;
}

D3D12_CPU_DESCRIPTOR_HANDLE Texture::RenderTargetView() const
{
	return renderTargetViewHeap->GetCPUDescriptorHandleForHeapStart();
}

D3D12_CPU_DESCRIPTOR_HANDLE Texture::DepthStencilView() const
{
	return depthStencilViewHeap->GetCPUDescriptorHandleForHeapStart();
}

D3D12_CPU_DESCRIPTOR_HANDLE Texture::ShaderResourceView() const
{
	return shaderResourceViewHeap->GetCPUDescriptorHandleForHeapStart();
}
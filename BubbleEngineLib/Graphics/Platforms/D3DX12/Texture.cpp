#include "Texture.h"

Texture::Texture(ID3D12Resource* buffer, D3D12_RESOURCE_STATES initialState)
	: buffer(buffer)
	, initialState(initialState)
{
	D3D12_RESOURCE_DESC desc = buffer->GetDesc();
	width = static_cast<uint32_t>(desc.Width);
	height = static_cast<uint32_t>(desc.Height);
	format = BEPixelFormat(desc.Format);
}

size_t Texture::Size() const
{
	return AlignTextureRowPitch(width * PixelFormatSize(format)) * height;
}
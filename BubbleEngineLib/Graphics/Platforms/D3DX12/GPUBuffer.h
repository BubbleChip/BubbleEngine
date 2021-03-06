#pragma once
#include "Graphics/BEGPUBuffer.h"
#include "Graphics/Platforms/D3DX12/d3dx12Include.h"

class GPUBuffer : public BEGPUBuffer
{
public:
	GPUBuffer(ID3D12Resource*, CPUCacheMode, D3D12_RESOURCE_STATES);
	~GPUBuffer() noexcept = default;

	size_t Size() const override { return size; }
	bool IsWritable() const override { return writable; };
	bool IsReadable() const override { return readable; };

	bool WriteData(const void* data, size_t size) override;
	bool WriteDataForTexture(const void* data, uint32_t width, uint32_t height, uint32_t formatSize) override;
	bool ReadData(void* data, size_t size) override;

	ID3D12Resource* Buffer() const { return buffer.Get(); }
	D3D12_RESOURCE_STATES InitialState() const { return initialState; }

private:
	size_t size;
	bool writable;
	bool readable;
	ComPtr<ID3D12Resource> buffer;
	D3D12_RESOURCE_STATES initialState;
};


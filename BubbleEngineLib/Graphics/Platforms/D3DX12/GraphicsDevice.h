#pragma once
#include "d3dx12Include.h"
#include "Graphics/BEGraphicsDevice.h"

using namespace Microsoft::WRL;

class GraphicsDevice final : public BEGraphicsDevice
{
public:
	GraphicsDevice();
	~GraphicsDevice() = default;

	BEObject<BECommandQueue> CreateCommandQueue() override;
	BEObject<BEGPUBuffer> CreateGPUBuffer(size_t size, BEGPUBuffer::CPUCacheMode mode) override;
	BEObject<BETexture> CreateTexture(const BETextureDescriptor& desc) override;

	ID3D12Device* Device() const { return device.Get(); }
	ComPtr<IDXGIFactory6> Factory() const { return factory; }

private:
	ComPtr<ID3D12Device> device;
	ComPtr<IDXGIFactory6> factory;

	D3D12_FEATURE_DATA_D3D12_OPTIONS d3d12Options;
	D3D12_FEATURE_DATA_ARCHITECTURE architecture;
};
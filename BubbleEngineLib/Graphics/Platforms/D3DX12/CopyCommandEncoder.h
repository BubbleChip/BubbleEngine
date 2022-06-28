#pragma once
#include "Graphics/BECopyCommandEncoder.h"
#include "d3dx12Include.h"
#include "CommandBuffer.h"

class CopyCommandEncoder final : public BECopyCommandEncoder
{
public:
	CopyCommandEncoder(CommandBuffer*, ID3D12GraphicsCommandList*);
	~CopyCommandEncoder() = default;

	void CopyBufferToBuffer(BEGPUBuffer* src, size_t srcOffset, BEGPUBuffer* dest, size_t destOffset, size_t copySize);

	void EndEncoding();

private:
	void TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES after, D3D12_RESOURCE_STATES before);

	BEObject<CommandBuffer> commandBuffer;
	ComPtr<ID3D12GraphicsCommandList> commandList;
};
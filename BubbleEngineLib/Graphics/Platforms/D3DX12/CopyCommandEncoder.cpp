#include "CopyCommandEncoder.h"
#include "Texture.h"
#include "GPUBuffer.h"


CopyCommandEncoder::CopyCommandEncoder(CommandBuffer* commandBuffer, ID3D12GraphicsCommandList* commandList)
    : commandBuffer(commandBuffer)
    , commandList(commandList)
{
}

void CopyCommandEncoder::CopyBufferToBuffer(BEGPUBuffer* src, size_t srcOffset, BEGPUBuffer* dest, size_t destOffset, size_t copySize)
{
    GPUBuffer* srcBuffer = dynamic_cast<GPUBuffer*>(src);
    GPUBuffer* destBuffer = dynamic_cast<GPUBuffer*>(dest);
    BEASSERT_DEBUG(srcBuffer);
    BEASSERT_DEBUG(destBuffer);

    ID3D12Resource* srcRawBuffer = srcBuffer->Buffer();
    ID3D12Resource* destRawBuffer = destBuffer->Buffer();
    BEASSERT_DEBUG(srcRawBuffer);
    BEASSERT_DEBUG(destRawBuffer);

    TransitionBufferState(destRawBuffer, destBuffer->InitialState(), D3D12_RESOURCE_STATE_COPY_DEST);
    commandList->CopyBufferRegion(destRawBuffer, destOffset, srcRawBuffer, srcOffset, copySize);
    TransitionBufferState(destRawBuffer, D3D12_RESOURCE_STATE_COPY_DEST, destBuffer->InitialState());
}

void CopyCommandEncoder::EndEncoding()
{
    commandList->Close();
    commandBuffer->AddEncodedCommandList(commandList.Get());
    commandList = nullptr;
}

void CopyCommandEncoder::TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES after, D3D12_RESOURCE_STATES before)
{
    if (before != after)
    {
        CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(buffer, before, after);
        commandList->ResourceBarrier(1, &barrier);
    }
}
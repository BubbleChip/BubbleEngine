#pragma once
#include "Graphics/BECommandQueue.h"
#include "d3dx12Include.h"
#include "GraphicsDevice.h"

class CommandQueue final : public BECommandQueue
{
public:
    CommandQueue(GraphicsDevice*, ID3D12CommandQueue*, ID3D12CommandAllocator*, ID3D12GraphicsCommandList*, ID3D12Fence*);
    ~CommandQueue() noexcept = default;

    BEObject<BESwapChain> CreateSwapChain(const BEWindow* _window) override;
    BEObject<BECommandBuffer> CreateCommandBuffer() override;

    ID3D12CommandQueue* Queue() const { return queue.Get(); }
    uint64_t ExecuteCommandLists(uint32_t numCommandLists, ID3D12CommandList* const* commandLists);

private:
    UINT64 currentFenceNumber;
    ComPtr<ID3D12Fence> fence;
    ComPtr<ID3D12CommandQueue> queue;
    BEObject<GraphicsDevice> device;

    ComPtr<ID3D12CommandAllocator> commandAllocator;
    ComPtr<ID3D12GraphicsCommandList> commandList;
};
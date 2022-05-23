#pragma once
#include "Graphics/BECommandQueue.h"
#include "d3dx12Include.h"
#include "GraphicsDevice.h"

class CommandQueue final : public BECommandQueue
{
public:
    CommandQueue(GraphicsDevice* _device, ID3D12CommandQueue* _queue);
    ~CommandQueue() noexcept = default;

    BEObject<BESwapChain> CreateSwapChain(const BEWindow* _window) override;

    ID3D12CommandQueue* Queue() const { return queue.Get(); }

private:
    ComPtr<ID3D12CommandQueue> queue;
    BEObject<GraphicsDevice> device;
};
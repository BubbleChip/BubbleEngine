#include "CommandQueue.h"
#include "SwapChain.h"

CommandQueue::CommandQueue(GraphicsDevice* _device, ID3D12CommandQueue* _queue, ID3D12CommandAllocator* _allocator, ID3D12GraphicsCommandList* _commandList, ID3D12Fence* _fence)
	: queue(_queue)
	, device(_device)
	, commandAllocator(_allocator)
	, commandList(_commandList)
	, fence(_fence)
{
}

BEObject<BESwapChain> CommandQueue::CreateSwapChain(const BEWindow* _window)
{
	return new SwapChain(device, this, _window);
}

BEObject<BECommandBuffer> CommandQueue::CreateCommandBuffer()
{
	return BEObject<BECommandBuffer>();
}

uint64_t CommandQueue::ExecuteCommandLists(uint32_t numCommandLists, ID3D12CommandList* const* commandLists)
{
	queue->ExecuteCommandLists(numCommandLists, commandLists);
	ThrowIfFailed(queue->Signal(fence.Get(), ++currentFenceNumber));
	return currentFenceNumber;
}

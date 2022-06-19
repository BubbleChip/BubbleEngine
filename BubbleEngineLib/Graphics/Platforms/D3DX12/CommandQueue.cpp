#include "CommandQueue.h"
#include "CommandBuffer.h"
#include "SwapChain.h"

CommandQueue::CommandQueue(GraphicsDevice* _device, ID3D12CommandQueue* _queue, ID3D12CommandAllocator* _allocator, ID3D12GraphicsCommandList* _commandList, ID3D12Fence* _fence)
	: queue(_queue)
	, device(_device)
	, commandAllocator(_allocator)
	, commandList(_commandList)
	, fence(_fence)
	, currentFenceNumber (0)
{
}

BEObject<BESwapChain> CommandQueue::CreateSwapChain(const BEWindow* _window)
{
	return new SwapChain(device, this, _window);
}

BEObject<BECommandBuffer> CommandQueue::CreateCommandBuffer()
{
	return new CommandBuffer(this, commandAllocator.Get(), commandList.Get(), D3D12_COMMAND_LIST_TYPE_DIRECT);
}

uint64_t CommandQueue::ExecuteCommandLists(uint32_t numCommandLists, ID3D12CommandList* const* commandLists)
{
	queue->ExecuteCommandLists(numCommandLists, commandLists);
	ThrowIfFailed(queue->Signal(fence.Get(), ++currentFenceNumber));
	return currentFenceNumber;
}

void CommandQueue::WaitComplete()
{
	// TODO :: LOCK 
	ThrowIfFailed(queue->Signal(fence.Get(), ++currentFenceNumber));
	if (fence->GetCompletedValue() < currentFenceNumber)
	{
		HANDLE eventHandle = CreateEvent(nullptr, false, false, nullptr);

		// Fire event when GPU hits current fence.  
		ThrowIfFailed(fence->SetEventOnCompletion(currentFenceNumber, eventHandle));

		// Wait until the GPU hits current fence event is fired.
		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}
}
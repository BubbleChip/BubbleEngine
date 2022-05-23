#include "CommandQueue.h"
#include "SwapChain.h"

CommandQueue::CommandQueue(GraphicsDevice* _device, ID3D12CommandQueue* _queue)
	: queue(_queue)
	, device(_device)
{
}

BEObject<BESwapChain> CommandQueue::CreateSwapChain(const BEWindow* _window)
{
	return new SwapChain(device, this, _window);
}

#include "CommandBuffer.h"
#include "RenderCommandEncoder.h"

CommandBuffer::CommandBuffer(CommandQueue* _commandQueue, ID3D12CommandAllocator* _allocator, ID3D12GraphicsCommandList* _list, D3D12_COMMAND_LIST_TYPE _type)
	: type(_type)
	, list(_list)
	, allocator(_allocator)
	, commandQueue(_commandQueue)
{
}

BEObject<BERenderCommandEncoder> CommandBuffer::CreateRenderCommandEncoder()
{
	list->Reset(allocator.Get(), nullptr);
	return new RenderCommandEncoder(this, list.Get());
}

void CommandBuffer::Commit()
{
	ID3D12CommandList* cmdLists[] = { list.Get() };
	commandQueue->ExecuteCommandLists(1, cmdLists);
}

void CommandBuffer::Reset()
{
	ThrowIfFailed(allocator->Reset());
}

void CommandBuffer::AddEncodedCommandList(ID3D12GraphicsCommandList* commandList)
{
	// not yet.
}
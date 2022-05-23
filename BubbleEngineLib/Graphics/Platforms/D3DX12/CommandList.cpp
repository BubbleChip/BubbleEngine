#include "CommandList.h"

CommandList::CommandList(ID3D12CommandAllocator* _allocator, ID3D12CommandList* _list, D3D12_COMMAND_LIST_TYPE _type)
	: type(_type)
	, list(_list)
	, allocator(_allocator)
{
}

void CommandList::Reset()
{
	ThrowIfFailed(allocator->Reset());
}

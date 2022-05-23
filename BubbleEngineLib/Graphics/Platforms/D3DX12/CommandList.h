#pragma once
#include "Graphics/BECommandList.h"
#include "d3dx12Include.h"
#include "GraphicsDevice.h"

class CommandList final : public BECommandList
{
public:
    CommandList(ID3D12CommandAllocator* _allocator, ID3D12CommandList* _list, D3D12_COMMAND_LIST_TYPE _type);
    ~CommandList() noexcept = default;

    void Reset();

private:
    D3D12_COMMAND_LIST_TYPE type;
    ComPtr<ID3D12CommandList> list;
    ComPtr<ID3D12CommandAllocator> allocator;
};
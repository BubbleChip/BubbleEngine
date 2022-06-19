#pragma once
#include "Graphics/BECommandBuffer.h"
#include "Graphics/BERenderCommandEncoder.h"
#include "d3dx12Include.h"
#include "GraphicsDevice.h"
#include "CommandQueue.h"

class CommandBuffer final : public BECommandBuffer
{
public:
    CommandBuffer(CommandQueue* _commandQueue, ID3D12CommandAllocator* _allocator, ID3D12GraphicsCommandList* _list, D3D12_COMMAND_LIST_TYPE _type);
    ~CommandBuffer() noexcept = default;

    BEObject<BERenderCommandEncoder> CreateRenderCommandEncoder() override;

    void Commit() override;

    void Reset();
    void AddEncodedCommandList(ID3D12GraphicsCommandList* commandList);

private:
    std::vector<ComPtr<ID3D12GraphicsCommandList>> encodedCommandList;

    D3D12_COMMAND_LIST_TYPE type;
    BEObject<CommandQueue> commandQueue;
    ComPtr<ID3D12GraphicsCommandList> list;
    ComPtr<ID3D12CommandAllocator> allocator;
};
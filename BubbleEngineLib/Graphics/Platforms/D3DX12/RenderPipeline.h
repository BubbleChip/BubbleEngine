#pragma once
#include "Graphics/BERenderPipeline.h"
#include "d3dx12Include.h"

class RenderPipeline final : public BERenderPipeline
{
public:
    RenderPipeline(ID3D12PipelineState*, ID3D12RootSignature*);
    ~RenderPipeline() noexcept = default;

    ID3D12PipelineState* PipelineState() const { return pipelineState.Get(); }
    ID3D12RootSignature* RootSignature() const { return rootSignature.Get(); }

private:
    ComPtr<ID3D12PipelineState> pipelineState;
    ComPtr<ID3D12RootSignature> rootSignature;
};
#include "RenderPipeline.h"

RenderPipeline::RenderPipeline(ID3D12PipelineState* pipelineState, ID3D12RootSignature* rootSignature)
    : pipelineState(pipelineState)
    , rootSignature(rootSignature)
{
}
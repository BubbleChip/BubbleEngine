#pragma once
#include "Graphics/BERenderCommandEncoder.h"
#include "d3dx12Include.h"
#include "CommandBuffer.h"

class RenderCommandEncoder : public BERenderCommandEncoder
{
public:
	RenderCommandEncoder(CommandBuffer*, ID3D12GraphicsCommandList*);
	~RenderCommandEncoder() = default;

	void SetViewport(const BEViewport& viewport) override;
	void SetViewports(const BEViewport* viewports, uint32_t count) override;
	void SetScissorRect(const BERect& rect) override;
	void SetScissorRects(const BERect* rects, uint32_t count) override;

	void SetRenderTargets(std::vector<const BETexture*> renderTargets, const BETexture* depthStencil) override;

	void ClearRenderTargetView(const BETexture* renderTarget, const BELinearColor& clearColor) override;
	void ClearDepthStencilView(const BETexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil) override;

	void EndEncoding() override;

private:
	void TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES after, D3D12_RESOURCE_STATES before);

	BEObject<CommandBuffer> commandBuffer;
	ComPtr<ID3D12GraphicsCommandList> commandList;
};

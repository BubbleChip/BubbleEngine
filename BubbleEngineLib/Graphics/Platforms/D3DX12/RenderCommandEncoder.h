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

	void SetVertexBuffer(const BEGPUBuffer* vertexBuffer, uint32_t vertexSize) override;
	void SetIndexBuffer(const BEGPUBuffer* indexBuffer, uint32_t indexSize) override;

	void SetConstantBuffer(uint32_t index, const BEGPUBuffer* constantBuffer) override;

	void DrawPrimitives(PrimitiveType primitiveType, uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexStart, uint32_t instanceStart) override;
	void DrawIndexedPrimitives(PrimitiveType primitiveType, uint32_t indexCount, uint32_t instanceCount, uint32_t indexOffset, uint32_t vertexOffset, uint32_t instanceStart) override;

	void SetPrimitiveType(PrimitiveType primitiveType);

	void EndEncoding() override;

private:
	void TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES after, D3D12_RESOURCE_STATES before);

	BEObject<CommandBuffer> commandBuffer;
	ComPtr<ID3D12GraphicsCommandList> commandList;
};

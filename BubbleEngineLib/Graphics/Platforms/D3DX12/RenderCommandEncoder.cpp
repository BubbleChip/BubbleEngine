#include "RenderCommandEncoder.h"
#include "texture.h"
#include "GPUBuffer.h"

RenderCommandEncoder::RenderCommandEncoder(CommandBuffer* commandBuffer, ID3D12GraphicsCommandList* commandList)
	: commandBuffer(commandBuffer)
	, commandList(commandList)
{
}

void RenderCommandEncoder::SetViewport(const BEViewport& viewport)
{
	D3D12_VIEWPORT vp
	{
		viewport.x, viewport.y,
		viewport.width, viewport.height,
		viewport.nearDepth, viewport.farDepth
	};
	commandList->RSSetViewports(1, &vp);
}

void RenderCommandEncoder::SetViewports(const BEViewport* viewports, uint32_t count)
{
	std::vector<D3D12_VIEWPORT> vps(count);
	for (uint32_t i = 0; i < count; ++i)
	{
		vps[i].TopLeftX = viewports[i].x;
		vps[i].TopLeftY = viewports[i].y;
		vps[i].Width = viewports[i].width;
		vps[i].Height = viewports[i].height;
		vps[i].MinDepth = viewports[i].nearDepth;
		vps[i].MaxDepth = viewports[i].farDepth;
	}
	commandList->RSSetViewports(count, vps.data());
}

void RenderCommandEncoder::SetScissorRect(const BERect& rect)
{
	D3D12_RECT rt
	{
	  static_cast<LONG>(rect.x),
	  static_cast<LONG>(rect.y),
	  static_cast<LONG>(rect.x + rect.width),
	  static_cast<LONG>(rect.y + rect.height)
	};
	commandList->RSSetScissorRects(1, &rt);
}

void RenderCommandEncoder::SetScissorRects(const BERect* rects, uint32_t count)
{
	std::vector<D3D12_RECT> rts(count);
	for (uint32_t i = 0; i < count; ++i)
	{
		rts[i].left = static_cast<LONG>(rects[i].x);
		rts[i].top = static_cast<LONG>(rects[i].y);
		rts[i].right = static_cast<LONG>(rects[i].x + rects[i].width);
		rts[i].bottom = static_cast<LONG>(rects[i].y + rects[i].height);
	}
	commandList->RSSetScissorRects(count, rts.data());
}

void RenderCommandEncoder::SetRenderTargets(std::vector<const BETexture*> renderTargets, const BETexture* depthStencil)
{
	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> renderTargetHandles;
	renderTargetHandles.reserve(renderTargets.size());
	for (const BETexture* renderTarget : renderTargets)
	{
		const Texture* rt = dynamic_cast<const Texture*>(renderTarget);

		renderTargetHandles.push_back(rt->RenderTargetView());
		TransitionBufferState(rt->Resource(), rt->InitialState(), D3D12_RESOURCE_STATE_RENDER_TARGET);
	}

	if (const Texture* ds = dynamic_cast<const Texture*>(depthStencil))
	{
		D3D12_CPU_DESCRIPTOR_HANDLE dsView = ds->DepthStencilView();
		commandList->OMSetRenderTargets(static_cast<UINT>(renderTargetHandles.size()), renderTargetHandles.data(),
			true, &dsView);
	}
	else
	{
		commandList->OMSetRenderTargets(static_cast<UINT>(renderTargetHandles.size()), renderTargetHandles.data(),
			false, nullptr);
	}

	for (const BETexture* renderTarget : renderTargets)
	{
		const Texture* rt = dynamic_cast<const Texture*>(renderTarget);

		TransitionBufferState(rt->Resource(), D3D12_RESOURCE_STATE_RENDER_TARGET, rt->InitialState());
	}
}

void RenderCommandEncoder::ClearRenderTargetView(const BETexture* renderTarget, const BELinearColor& clearColor)
{
	const Texture* rt = dynamic_cast<const Texture*>(renderTarget);
	BEASSERT_DEBUG(rt);

	TransitionBufferState(rt->Resource(), rt->InitialState(), D3D12_RESOURCE_STATE_RENDER_TARGET);
	commandList->ClearRenderTargetView(rt->RenderTargetView(), clearColor.value, 0, nullptr);
	TransitionBufferState(rt->Resource(), D3D12_RESOURCE_STATE_RENDER_TARGET, rt->InitialState());
}

void RenderCommandEncoder::ClearDepthStencilView(const BETexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil)
{
	D3D12_CLEAR_FLAGS flag = D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL;
	switch (clearFlag)
	{
	case DepthStencilClearFlag::Depth:
		flag = D3D12_CLEAR_FLAG_DEPTH;
		break;
	case DepthStencilClearFlag::Stencil:
		flag = D3D12_CLEAR_FLAG_STENCIL;
		break;
	}

	const Texture* ds = dynamic_cast<const Texture*>(depthStencil);

	commandList->ClearDepthStencilView(ds->DepthStencilView(), flag, clearDepth, clearStencil, 0, nullptr);
}

void RenderCommandEncoder::SetVertexBuffer(const BEGPUBuffer* vertexBuffer, uint32_t vertexSize)
{
	const GPUBuffer* vb = dynamic_cast<const GPUBuffer*>(vertexBuffer);
	BEASSERT_DEBUG(vb);

	D3D12_VERTEX_BUFFER_VIEW view;
	view.BufferLocation = vb->Buffer()->GetGPUVirtualAddress();
	view.StrideInBytes = vertexSize;
	view.SizeInBytes = static_cast<UINT>(vb->Size());
	commandList->IASetVertexBuffers(0, 1, &view);
}

void RenderCommandEncoder::SetIndexBuffer(const BEGPUBuffer* indexBuffer, uint32_t indexSize)
{
	BEASSERT_DEBUG(indexSize == 2 || indexSize == 4);

	const GPUBuffer* ib = dynamic_cast<const GPUBuffer*>(indexBuffer);
	BEASSERT_DEBUG(ib);

	D3D12_INDEX_BUFFER_VIEW view;
	view.BufferLocation = ib->Buffer()->GetGPUVirtualAddress();
	view.Format = indexSize == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
	view.SizeInBytes = static_cast<UINT>(ib->Size());
	commandList->IASetIndexBuffer(&view);
}

void RenderCommandEncoder::SetConstantBuffer(uint32_t index, const BEGPUBuffer* constantBuffer)
{
	const GPUBuffer* cb = dynamic_cast<const GPUBuffer*>(constantBuffer);
	BEASSERT_DEBUG(cb);
	commandList->SetGraphicsRootConstantBufferView(index, cb->Buffer()->GetGPUVirtualAddress());
}

void RenderCommandEncoder::DrawPrimitives(PrimitiveType primitiveType, uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexStart, uint32_t instanceStart)
{
	SetPrimitiveType(primitiveType);
	commandList->DrawInstanced(vertexCount, instanceCount, vertexStart, instanceStart);
}

void RenderCommandEncoder::DrawIndexedPrimitives(PrimitiveType primitiveType, uint32_t indexCount, uint32_t instanceCount, uint32_t indexOffset, uint32_t vertexOffset, uint32_t instanceStart)
{
	SetPrimitiveType(primitiveType);
	commandList->DrawIndexedInstanced(indexCount, instanceCount, indexOffset, vertexOffset, instanceStart);
}

void RenderCommandEncoder::SetPrimitiveType(PrimitiveType primitiveType)
{
	switch (primitiveType)
	{
	case PrimitiveType::Point:
		commandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		break;
	case PrimitiveType::Line:
		commandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	case PrimitiveType::LineStrip:
		commandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		break;
	case PrimitiveType::Triangle:
		commandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case PrimitiveType::TriangleStrip:
		commandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		break;
	}
}


void RenderCommandEncoder::EndEncoding()
{
	commandList->Close();
	commandBuffer->AddEncodedCommandList(commandList.Get());
	commandList = nullptr;
}

void RenderCommandEncoder::TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES after, D3D12_RESOURCE_STATES before)
{
	if (before != after)
	{
		CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(buffer, before, after);
		commandList->ResourceBarrier(1, &barrier);
	}
}
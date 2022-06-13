#include "RenderCommandEncoder.h"
#include "texture.h"

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
		BEASSERT_DEBUG(rt);

		renderTargetHandles.push_back(rt->RenderTargetView());
		TransitionBufferState(rt->Resource(), rt->InitialState(), D3D12_RESOURCE_STATE_RENDER_TARGET);
	}

	BEASSERT_DEBUG(renderTargetHandles.size() > 0);

	//if (const Texture* ds = dynamic_cast<const Texture*>(depthStencil))
	//{
	//	D3D12_CPU_DESCRIPTOR_HANDLE dsView = ds->DepthStencilView();
	//	commandList->OMSetRenderTargets(static_cast<UINT>(renderTargetHandles.size()), renderTargetHandles.data(),
	//		true, &dsView);
	//}
	//else
	//{
		commandList->OMSetRenderTargets(static_cast<UINT>(renderTargetHandles.size()), renderTargetHandles.data(),
			false, nullptr);
	//}

	for (const BETexture* renderTarget : renderTargets)
	{
		const Texture* rt = dynamic_cast<const Texture*>(renderTarget);
		BEASSERT_DEBUG(rt);

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

void RenderCommandEncoder::EndEncoding()
{
	commandList->Close();
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
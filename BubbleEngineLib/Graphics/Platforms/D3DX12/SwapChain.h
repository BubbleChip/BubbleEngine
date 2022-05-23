#pragma once
#include "Graphics/BESwapChain.h"
#include "d3dx12Include.h"
#include "BECore/BEObject.h"
#include "GraphicsDevice.h"

class BEWindow;
class CommandQueue;

class SwapChain final : public BESwapChain
{
public:
	SwapChain(GraphicsDevice* _device, CommandQueue* _queue, const BEWindow* _window);
	~SwapChain() noexcept = default;

	uint32_t Width() override { return width; }
	uint32_t Height() override { return height; }

	void Resize(uint32_t _width, uint32_t _height) override;

private:
	uint32_t width;
	uint32_t height;

	UINT currentColorTextureIndex;
	mutable ComPtr<ID3D12Resource> colorTexture[FRAME_BUFFER_COUNT];
	mutable ComPtr<ID3D12Resource> depthStencilTexture;

	ComPtr<IDXGISwapChain3> swapChain;

	BEObject<GraphicsDevice> device;
};
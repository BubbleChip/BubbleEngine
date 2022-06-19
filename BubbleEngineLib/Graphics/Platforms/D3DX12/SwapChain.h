#pragma once
#include "Graphics/BESwapChain.h"
#include "d3dx12Include.h"
#include "BECore/BEObject.h"
#include "GraphicsDevice.h"
#include "Texture.h"

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
	void Present() override;

	const BETexture* CurrentColorTexture() const override;
	const BETexture* DepthStencilTexture() const override;

private:
	void SetupColorTextures();
	void SetupDepthStencil();

	uint32_t width;
	uint32_t height;

	UINT currentColorTextureIndex;
	mutable BEObject<Texture> colorTexture[FRAME_BUFFER_COUNT];
	mutable BEObject<Texture> depthStencilTexture;

	ComPtr<IDXGISwapChain3> swapChain;

	BEObject<GraphicsDevice> device;
};
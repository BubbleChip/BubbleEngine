#pragma once
#include "BECore/BEInclude.h"
#include "BECore/BERefCounter.h"

class BETexture;

class BEL_API BESwapChain : public BERefCounter
{
public :
	enum { FRAME_BUFFER_COUNT = 2 };

	BESwapChain() = default;
	virtual ~BESwapChain() = default;

	virtual uint32_t Width() = 0;
	virtual uint32_t Height() = 0;

	virtual const BETexture* CurrentColorTexture() const = 0;
	virtual const BETexture* DepthStencilTexture() const = 0;

	virtual void Resize(uint32_t _width, uint32_t height) = 0;
	virtual void Present() = 0;
};
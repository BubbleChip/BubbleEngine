#pragma once

#include "BECore/BEInclude.h"
#include "BECore/BEObject.h"
#include "BEGPUBuffer.h"
#include "BECommandQueue.h"

class BEL_API BEGraphicsDevice : public BERefCounter
{
public:
	virtual ~BEGraphicsDevice() = default;

	virtual BEObject<BECommandQueue> CreateCommandQueue() = 0;
	virtual BEObject<BEGPUBuffer> CreateGPUBuffer(size_t size, BEGPUBuffer::CPUCacheMode mode) = 0;
	virtual BEObject<BETexture> CreateTexture(const BETextureDescriptor& descriptor) = 0;

	
	static BEGraphicsDevice* CreateGraphicsDevice();

protected:
	BEGraphicsDevice() = default;
};
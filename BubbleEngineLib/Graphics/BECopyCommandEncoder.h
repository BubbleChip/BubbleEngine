#pragma once
#include "BECore/BEInclude.h"
#include "BECore/BEObject.h"

class BEGPUBuffer;

class BEL_API BECopyCommandEncoder : public BERefCounter
{
public:
	struct TextureArea
	{
		uint32_t x, y;
		uint32_t width, height;
	};

	BECopyCommandEncoder() = default;
	virtual ~BECopyCommandEncoder() = default;

	virtual void CopyBufferToBuffer(BEGPUBuffer* src, size_t srcOffset, BEGPUBuffer* dest, size_t destOffset, size_t copySize) = 0;
	
	virtual void EndEncoding() = 0;
};
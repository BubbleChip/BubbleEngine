#pragma once
#include "BECore/BEInclude.h"
#include "BECore/BERefCounter.h"

class BEL_API BEGPUBuffer : public BERefCounter
{
public:
	enum CPUCacheMode
	{
		None = 0,		// The resource can be accessed only by the GPU.
		WriteCombined,	// the CPU writes into, but never reads.
		ReadCombined,	// the CPU reads into, but never write.
	};


	BEGPUBuffer() = default;
	virtual ~BEGPUBuffer() noexcept = default;

	virtual size_t Size() const = 0;
	virtual bool IsWritable() const = 0;
	virtual bool IsReadable() const = 0;

	virtual bool WriteData(const void* data, size_t size) = 0;
	virtual bool WriteDataForTexture(const void* data, uint32_t width, uint32_t height, uint32_t formatSize) = 0;
	virtual bool ReadData(void* data, size_t size) = 0;
};
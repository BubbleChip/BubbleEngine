#pragma once

#include "BECore/BEInclude.h"
#include "BECore/BEObject.h"
#include "BEGPUBuffer.h"
#include "BECommandQueue.h"
#include "BERenderPipeline.h"
#include <string>

class BEL_API BEGraphicsDevice : public BERefCounter
{
public:
	virtual ~BEGraphicsDevice() = default;

	virtual BEObject<BECommandQueue> CreateCommandQueue() = 0;
	virtual BEObject<BEGPUBuffer> CreateGPUBuffer(size_t size, BEGPUBuffer::CPUCacheMode mode) = 0;
	virtual BEObject<BETexture> CreateTexture(const BETextureDescriptor& descriptor) = 0;

	virtual BEObject<BERenderPipeline> CreateRenderPipeline(const BERenderPipelineDescriptor& descriptor) = 0;
	
	static BEGraphicsDevice* CreateGraphicsDevice();

	virtual BEObject<BEShader> CreateShader(const std::wstring path, const std::string& entry, BEShader::StageType stage);
	virtual BEObject<BEShader> CreateShader(const std::vector<uint8_t>& path, const std::string& entry, BEShader::StageType stage) = 0;

protected:
	BEGraphicsDevice() = default;
};
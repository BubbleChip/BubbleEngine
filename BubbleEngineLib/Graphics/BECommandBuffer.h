#pragma once
#include "BECore/BEInclude.h"
#include "BECore/BERefCounter.h"
#include "BECore/BEObject.h"
#include "BERenderCommandEncoder.h"
#include "BERenderPipeline.h"

class BEL_API BECommandBuffer : public BERefCounter
{
public:
	BECommandBuffer() = default;
	virtual ~BECommandBuffer() = default;

	virtual BEObject<BERenderCommandEncoder> CreateRenderCommandEncoder(BERenderPipeline* pipelineState) = 0;

	virtual void Commit() = 0;
};
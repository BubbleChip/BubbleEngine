#pragma once
#include "BECore/BEInclude.h"
#include "BECore/BERefCounter.h"
#include "Graphics/BERenderCommandEncoder.h"
#include "BECore/BEObject.h"

class BEL_API BECommandBuffer : public BERefCounter
{
public:
	BECommandBuffer() = default;
	virtual ~BECommandBuffer() = default;

	virtual BEObject<BERenderCommandEncoder> CreateRenderCommandEncoder() = 0;

	virtual void Commit() = 0;
};
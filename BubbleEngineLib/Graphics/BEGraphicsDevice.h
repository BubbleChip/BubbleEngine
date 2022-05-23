#pragma once

#include "BECore/BEInclude.h"
#include "BECore/BEObject.h"
#include "BECommandList.h"
#include "BECommandQueue.h"

class BEL_API BEGraphicsDevice : public BERefCounter
{
public:
	virtual ~BEGraphicsDevice() = default;

	virtual BEObject<BECommandQueue> CreateCommandQueue() = 0;
	virtual BEObject<BECommandList> CreateCommandList() = 0;

	
	static BEGraphicsDevice* CreateGraphicsDevice();

protected:
	BEGraphicsDevice() = default;
};
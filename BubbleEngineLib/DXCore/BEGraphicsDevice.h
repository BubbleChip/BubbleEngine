#pragma once

#include "../BECore/BEInclude.h"
#include "../BECore/BERefCounter.h"

class BEL_API BEGraphicsDevice : public BERefCounter
{
public:
	virtual ~BEGraphicsDevice() = default;

	
	static BEGraphicsDevice* CreateGraphicsDevice();

protected:
	BEGraphicsDevice() = default;
};
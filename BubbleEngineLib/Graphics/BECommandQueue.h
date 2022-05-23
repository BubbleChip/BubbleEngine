#pragma once
#include "BECore/BEInclude.h"
#include "BECore/BEObject.h"
#include "BESwapChain.h"

class BEWindow;

class BEL_API BECommandQueue : public BERefCounter
{
public:
	BECommandQueue() = default;
	virtual ~BECommandQueue() = default;

	virtual BEObject<BESwapChain> CreateSwapChain(const BEWindow* _window) = 0;
};
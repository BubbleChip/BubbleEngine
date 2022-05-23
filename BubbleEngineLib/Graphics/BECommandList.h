#pragma once
#include "BECore/BEInclude.h"
#include "BECore/BERefCounter.h"

class BEL_API BECommandList : public BERefCounter
{
public:
	BECommandList() = default;
	virtual ~BECommandList() = default;
};
#pragma once
#include <stdint.h>
#include <atomic>
#include "BEInclude.h"

class BERefCounter
{
public:
	BERefCounter();

//protected:
	virtual ~BERefCounter();

	uint32_t AddRef();
	uint32_t ReleaseRef();
	uint32_t GetRefCount() const;


private:
	struct BEL_API std::atomic<unsigned int> refCount = 0;
};


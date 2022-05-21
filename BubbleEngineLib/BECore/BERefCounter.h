#pragma once
#include <stdint.h>

class BERefCounter
{
public:
	BERefCounter();

protected:
	virtual ~BERefCounter();

	uint32_t AddRef();
	uint32_t ReleaseRef();
	uint32_t GetRefCount() const;


private:
	uint32_t refCount = 0;
};


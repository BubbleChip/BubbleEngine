#include "BERefCounter.h"
#include "BEInclude.h"

BERefCounter::BERefCounter()
	: refCount(0)
{
}

BERefCounter::~BERefCounter()
{
	BEASSERT(refCount == 0);
}

uint32_t BERefCounter::AddRef()
{
	++refCount;
	return refCount;
}

uint32_t BERefCounter::ReleaseRef()
{
	--refCount;
	return refCount;
}

uint32_t BERefCounter::GetRefCount() const
{
	return refCount;
}

#pragma once
#include "BECore/BEInclude.h"
#include "BECore/BERefCounter.h"
#include "BEPixelFormat.h"

class BEL_API BETexture : public BERefCounter
{
public:
	BETexture() = default;
	virtual ~BETexture() noexcept = default;

	virtual size_t Size() const = 0;
	virtual uint32_t Width() const = 0;
	virtual uint32_t Height() const = 0;
	virtual BEPixelFormat Format() const = 0;

};
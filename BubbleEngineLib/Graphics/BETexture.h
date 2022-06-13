#pragma once
#include "BECore/BEInclude.h"
#include "BECore/BERefCounter.h"
#include "BEPixelFormat.h"

class BEL_API BETexture : public BERefCounter
{
public:
	enum Type
	{
		Type1D,
		Type2D,
		Type3D,
	};
	enum Usage : uint32_t
	{
		UsageNone = 0U,
		UsageShaderRead = 1U,
		UsageRenderTarget = 1U << 1,
		UsageDepthStencil = 1U << 2,
	};

	BETexture() = default;
	virtual ~BETexture() noexcept = default;

	virtual size_t Size() const = 0;
	virtual uint32_t Width() const = 0;
	virtual uint32_t Height() const = 0;
	virtual BEPixelFormat Format() const = 0;

};

struct BETextureDescriptor
{
	BETexture::Type type;
	BEPixelFormat format;
	uint32_t width;
	uint32_t height;
	uint32_t depth;
	uint32_t mipmapLevelCount;
	uint32_t sampleCount;
	uint32_t usage;
};
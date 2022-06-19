#pragma once
#include "BECore/BEInclude.h"
#include "BEViewport.h"
#include "BETexture.h"
#include "BELinearColor.h"
#include "Math/BERect.h"
#include <vector>
#include "BECore/BEObject.h"

class BERenderCommandEncoder : public BERefCounter
{
public:
    enum class DepthStencilClearFlag
    {
        Depth,
        Stencil,
        All,
    };

    BERenderCommandEncoder() = default;
    virtual ~BERenderCommandEncoder() noexcept = default;

    virtual void SetViewport(const BEViewport& viewport) = 0;
    virtual void SetViewports(const BEViewport* viewports, uint32_t count) = 0;
    virtual void SetScissorRect(const BERect& rect) = 0;
    virtual void SetScissorRects(const BERect* rects, uint32_t count) = 0;

    virtual void SetRenderTargets(std::vector<const BETexture*> renderTargets, const BETexture* depthStencil) = 0;
    virtual void ClearRenderTargetView(const BETexture* renderTarget, const BELinearColor& clearColor) = 0;
    virtual void ClearDepthStencilView(const BETexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil) = 0;

    virtual void EndEncoding() = 0;
};


#pragma once
#include "BECore/BEInclude.h"
#include "BEViewport.h"
#include "BETexture.h"
#include "BELinearColor.h"
#include "Math/BERect.h"
#include <vector>
#include "BECore/BEObject.h"

class BEGPUBuffer;

class BERenderCommandEncoder : public BERefCounter
{
public:
    enum class DepthStencilClearFlag
    {
        Depth,
        Stencil,
        All,
    };
    enum class PrimitiveType
    {
        Point,
        Line,
        LineStrip,
        Triangle,
        TriangleStrip,
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

    virtual void SetVertexBuffer(const BEGPUBuffer* vertexBuffer, uint32_t vertexSize) = 0;
    virtual void SetIndexBuffer(const BEGPUBuffer* indexBuffer, uint32_t indexSize) = 0;

    virtual void SetConstantBuffer(uint32_t index, const BEGPUBuffer* constantBuffer) = 0;

    virtual void DrawPrimitives(PrimitiveType primitiveType, uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexStart, uint32_t instanceStart) = 0;
    virtual void DrawIndexedPrimitives(PrimitiveType primitiveType, uint32_t indexCount, uint32_t instanceCount, uint32_t indexOffset, uint32_t vertexOffset, uint32_t instanceStart) = 0;


    virtual void EndEncoding() = 0;
};


#pragma once
#include "Graphics/BEVertexDescriptor.h"
#include "Graphics/BERenderPipeline.h"
#include "Graphics/BEBlendState.h"
#include "d3dx12Include.h"

inline DXGI_FORMAT PixelFormat(BEPixelFormat format)
{
    switch (format)
    {
    case BEPixelFormat::RGBA8Unorm:
        return DXGI_FORMAT_R8G8B8A8_UNORM;
    case BEPixelFormat::RGBA8Uint:
        return DXGI_FORMAT_R8G8B8A8_UINT;
    case BEPixelFormat::Depth24UnormStencil8:
        return DXGI_FORMAT_D24_UNORM_S8_UINT;
    }
    return DXGI_FORMAT_UNKNOWN;
}

inline BEPixelFormat PixelFormat(DXGI_FORMAT format)
{
    switch (format)
    {
    case DXGI_FORMAT_R8G8B8A8_UNORM:
        return BEPixelFormat::RGBA8Unorm;
    case DXGI_FORMAT_R8G8B8A8_UINT:
        return BEPixelFormat::RGBA8Uint;
    case DXGI_FORMAT_D24_UNORM_S8_UINT:
        return BEPixelFormat::Depth24UnormStencil8;
    }
    return BEPixelFormat::Invalid;
}

inline DXGI_FORMAT VertexFormat(BEVertexFormat format)
{
    switch (format)
    {
    case BEVertexFormat::Float:
        return DXGI_FORMAT_D32_FLOAT;
    case BEVertexFormat::Float2:
        return DXGI_FORMAT_R32G32_FLOAT;
    case BEVertexFormat::Float3:
        return DXGI_FORMAT_R32G32B32_FLOAT;
    case BEVertexFormat::Float4:
        return DXGI_FORMAT_R32G32B32A32_FLOAT;
    }
    return DXGI_FORMAT_UNKNOWN;
}

inline D3D12_PRIMITIVE_TOPOLOGY_TYPE PrimitiveType(BEPrimitiveTopologyType type)
{
    switch (type)
    {
    case BEPrimitiveTopologyType::Point:
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
    case BEPrimitiveTopologyType::Line:
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
    case BEPrimitiveTopologyType::Triangle:
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    }
    return D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED;
}

inline D3D12_BLEND_OP BlendOperation(BEBlendOperation type)
{
    switch (type)
    {
    case BEBlendOperation::Add:
        return D3D12_BLEND_OP_ADD;
    case BEBlendOperation::Subtract:
        return D3D12_BLEND_OP_SUBTRACT;
    case BEBlendOperation::ReverseSubtract:
        return D3D12_BLEND_OP_REV_SUBTRACT;
    case BEBlendOperation::Min:
        return D3D12_BLEND_OP_MIN;
    case BEBlendOperation::Max:
        return D3D12_BLEND_OP_MAX;
    default:
        BEASSERT_DEBUG(false);
    }
    return D3D12_BLEND_OP_ADD;
}

inline D3D12_BLEND BlendFactor(BEBlendFactor type)
{
    switch (type)
    {
    case BEBlendFactor::Zero:
        return D3D12_BLEND_ZERO;
    case BEBlendFactor::One:
        return D3D12_BLEND_ONE;
    case BEBlendFactor::SourceColor:
        return D3D12_BLEND_SRC_COLOR;
    case BEBlendFactor::OneMinusSourceColor:
        return D3D12_BLEND_INV_SRC_COLOR;
    case BEBlendFactor::SourceAlpha:
        return D3D12_BLEND_SRC_ALPHA;
    case BEBlendFactor::OneMinusSourceAlpha:
        return D3D12_BLEND_INV_SRC_ALPHA;
    case BEBlendFactor::DestinationColor:
        return D3D12_BLEND_DEST_COLOR;
    case BEBlendFactor::OneMinusDestinationColor:
        return D3D12_BLEND_INV_DEST_COLOR;
    case BEBlendFactor::DestinationAlpha:
        return D3D12_BLEND_DEST_ALPHA;
    case BEBlendFactor::OneMinusDestinationAlpha:
        return D3D12_BLEND_INV_DEST_ALPHA;
    case BEBlendFactor::SourceAlphaSaturated:
        return D3D12_BLEND_SRC_ALPHA_SAT;
    case BEBlendFactor::BlendFactor:
        return D3D12_BLEND_BLEND_FACTOR;
    case BEBlendFactor::OneMinusBlendFactor:
        return D3D12_BLEND_INV_BLEND_FACTOR;
    default:
        BEASSERT_DEBUG(false);
    }
    return D3D12_BLEND_ONE;
}
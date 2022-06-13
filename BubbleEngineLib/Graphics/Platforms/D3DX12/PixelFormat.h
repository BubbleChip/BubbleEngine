#pragma once
#include "Graphics/BEPixelFormat.h"
#include "Graphics/Platforms/D3DX12/d3dx12Include.h"

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
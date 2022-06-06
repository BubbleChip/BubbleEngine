#pragma once
#include <stdint.h>

enum class BEPixelFormat
{
    Invalid,

    // RGBA 8
    RGBA8Unorm,
    RGBA8Uint,

    // Depth Stencil
    Depth24UnormStencil8,
};

inline uint32_t PixelFormatSize(BEPixelFormat format)
{
    switch (format)
    {
    case BEPixelFormat::RGBA8Unorm:
    case BEPixelFormat::RGBA8Uint:
    case BEPixelFormat::Depth24UnormStencil8:
        return 4;

    default:
        //TODO : ERROR LOG
        break;
    }
    return 0;
}
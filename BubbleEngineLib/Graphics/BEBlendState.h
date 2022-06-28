#pragma once

enum BEColorWriteMask
{
    ColorWriteMaskNone = 0x0,
    ColorWriteMaskRed = 0x1,
    ColorWriteMaskGreen = 0x2,
    ColorWriteMaskBlue = 0x4,
    ColorWriteMaskAlpha = 0x8,
    ColorWriteMaskAll = 0xf,
};

enum class BEBlendOperation
{
    Add,
    Subtract,
    ReverseSubtract,
    Min,
    Max
};

enum class BEBlendFactor
{
    Zero,
    One,
    SourceColor,
    OneMinusSourceColor,
    SourceAlpha,
    OneMinusSourceAlpha,
    DestinationColor,
    OneMinusDestinationColor,
    DestinationAlpha,
    OneMinusDestinationAlpha,
    SourceAlphaSaturated,
    BlendFactor,
    OneMinusBlendFactor,
};
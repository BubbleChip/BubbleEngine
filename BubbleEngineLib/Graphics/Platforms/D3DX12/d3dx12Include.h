#pragma once
#include "d3dx12.h"
#include <dxgi1_6.h>
#include <wrl.h>
#include <system_error>
#include <D3Dcompiler.h>

#if defined(DEBUG) || defined(_DEBUG)
#include <dxgidebug.h>
#endif

using namespace Microsoft::WRL;

inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        auto msg = std::system_category().message(hr);
        throw std::exception(msg.c_str());
    }
}

constexpr inline uint32_t AlignGPUBufferSize(size_t size)
{
    constexpr uint32_t alignmentSize = D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT - 1;
    return (size + alignmentSize) & ~(alignmentSize);
}

constexpr inline uint32_t AlignTextureRowPitch(size_t size)
{
#if (defined(XBOX_ONE) && defined(_TITLE)) || defined(_GAMING_XBOX)
    constexpr uint32_t alignmentSize = D3D12XBOX_TEXTURE_DATA_PITCH_ALIGNMENT - 1;
#else
    constexpr uint32_t alignmentSize = D3D12_TEXTURE_DATA_PITCH_ALIGNMENT - 1;
#endif
    return (size + alignmentSize) & ~(alignmentSize);
}
namespace GraphicsOption
{
    constexpr bool ENABLE_DEBUG_LAYER = 1;
    constexpr bool ENABLE_GPU_VALIDATION = 1;
    constexpr D3D_FEATURE_LEVEL MIN_FEATURE = D3D_FEATURE_LEVEL_11_0;
}
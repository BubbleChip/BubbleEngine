#pragma once
#include <stdint.h>
#include <vector>

enum class BEVertexFormat
{
    Invalid = 0,

    Float,
    Float2,
    Float3,
    Float4,
};

struct BEVertexAttributeDescriptor
{
    BEVertexFormat format;
    const char* semanticName;
    uint32_t semanticIndex;
    uint32_t offset;
};

struct BEVertexDescriptor
{
    std::vector<BEVertexAttributeDescriptor> attributes;
};
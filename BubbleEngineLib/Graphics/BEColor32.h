#pragma once
#include "BECore/BEInclude.h"
#include <algorithm>
#include <cstdint>

class BEColor32 final
{
public:
    BEColor32();
    explicit BEColor32(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    explicit BEColor32(uint32_t value);

    bool operator != (const BEColor32& c) const;
    bool operator == (const BEColor32& c) const;

    BEColor32 operator + (const BEColor32& c) const;
    BEColor32 operator - (const BEColor32& c) const;

    BEColor32& operator += (const BEColor32& c);
    BEColor32& operator -= (const BEColor32& c);

    union
    {
        struct
        {
            uint8_t r, g, b, a;
        };
        uint32_t value;
    };
};
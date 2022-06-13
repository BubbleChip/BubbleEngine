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

BEColor32::BEColor32()
    : r(0), g(0), b(0), a(255)
{}
BEColor32::BEColor32(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : r(r), g(g), b(b), a(a)
{}
BEColor32::BEColor32(uint32_t value)
    : value(value)
{}

bool BEColor32::operator==(const BEColor32& c) const
{
    return r == c.r && g == c.g && b == c.b && a == c.a;
}
bool BEColor32::operator!=(const BEColor32& c) const
{
    return r != c.r || g != c.g || b != c.b || a != c.a;
}

BEColor32 BEColor32::operator+(const BEColor32& c) const
{
    return BEColor32(
        static_cast<uint8_t>(std::clamp(r + c.r, 0, 255)),
        static_cast<uint8_t>(std::clamp(g + c.g, 0, 255)),
        static_cast<uint8_t>(std::clamp(b + c.b, 0, 255)),
        static_cast<uint8_t>(std::clamp(a + c.a, 0, 255)));
}
BEColor32 BEColor32::operator-(const BEColor32& c) const
{
    return BEColor32(
        static_cast<uint8_t>(std::clamp(r - c.r, 0, 255)),
        static_cast<uint8_t>(std::clamp(g - c.g, 0, 255)),
        static_cast<uint8_t>(std::clamp(b - c.b, 0, 255)),
        static_cast<uint8_t>(std::clamp(a - c.a, 0, 255)));
}

BEColor32& BEColor32::operator+=(const BEColor32& c)
{
    r = static_cast<uint8_t>(std::clamp(r + c.r, 0, 255));
    g = static_cast<uint8_t>(std::clamp(g + c.g, 0, 255));
    b = static_cast<uint8_t>(std::clamp(b + c.b, 0, 255));
    a = static_cast<uint8_t>(std::clamp(a + c.a, 0, 255));
    return *this;
}
BEColor32& BEColor32::operator-=(const BEColor32& c)
{
    r = static_cast<uint8_t>(std::clamp(r - c.r, 0, 255));
    g = static_cast<uint8_t>(std::clamp(g - c.g, 0, 255));
    b = static_cast<uint8_t>(std::clamp(b - c.b, 0, 255));
    a = static_cast<uint8_t>(std::clamp(a - c.a, 0, 255));
    return *this;
}
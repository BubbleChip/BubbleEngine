#include "BELinearColor.h"

const BELinearColor BELinearColor::white = BELinearColor(1.0f,1.0f,1.0f,1.0f);

BELinearColor::BELinearColor()
    : r(0.f), g(0.f), b(0.f), a(1.f)
{}
BELinearColor::BELinearColor(float r, float g, float b, float a)
    : r(r), g(g), b(b), a(a)
{}
BELinearColor::BELinearColor(uint16_t r, uint16_t g, uint16_t b, uint16_t a, uint16_t colorDepth)
    : BELinearColor()
{
    BEASSERT_DEBUG(colorDepth > 0);

    float factor = 1.f / ((1 << colorDepth) - 1);
    this->r = r * factor;
    this->g = g * factor;
    this->b = b * factor;
    this->a = a * factor;
}
BELinearColor::BELinearColor(BEColor32 color32)
{
    constexpr float factor = { 1.f / 255.f };
    r = static_cast<float>(color32.r) * factor;
    g = static_cast<float>(color32.g) * factor;
    b = static_cast<float>(color32.b) * factor;
    a = static_cast<float>(color32.a) * factor;

}
BELinearColor::BELinearColor(const BEVector3& v)
    : r(v.x), g(v.y), b(v.z), a(1.f)
{}
BELinearColor::BELinearColor(const BEVector4& v)
    : r(v.x), g(v.y), b(v.z), a(v.w)
{}

bool BELinearColor::operator==(const BELinearColor& c) const
{
    return r == c.r && g == c.g && b == c.b && a == c.a;
}
bool BELinearColor::operator!=(const BELinearColor& c) const
{
    return r != c.r || g != c.g || b != c.b || a != c.a;
}

BELinearColor BELinearColor::operator+(const BELinearColor& c) const
{
    return { r + c.r, g + c.g, b + c.b, a + c.a };
}
BELinearColor BELinearColor::operator-(const BELinearColor& c) const
{
    return { r - c.r, g - c.g, b - c.b, a - c.a };
}
BELinearColor BELinearColor::operator*(const BELinearColor& c) const
{
    return { r * c.r, g * c.g, b * c.b, a * c.a };
}
BELinearColor BELinearColor::operator*(float f) const
{
    return { r * f, g * f, b * f, a * f };
}

BELinearColor& BELinearColor::operator+=(const BELinearColor& c)
{
    r = r + c.r;
    g = g + c.g;
    b = b + c.b;
    a = a + c.a;
    return *this;
}
BELinearColor& BELinearColor::operator-=(const BELinearColor& c)
{
    r = r - c.r;
    g = g - c.g;
    b = b - c.b;
    a = a - c.a;
    return *this;
}
BELinearColor& BELinearColor::operator*=(const BELinearColor& c)
{
    r = r * c.r;
    g = g * c.g;
    b = b * c.b;
    a = a * c.a;
    return *this;
}
BELinearColor& BELinearColor::operator*=(float f)
{
    r = r * f;
    g = g * f;
    b = b * f;
    a = a * f;
    return *this;
}
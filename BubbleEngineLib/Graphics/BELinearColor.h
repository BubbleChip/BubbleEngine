#pragma once
#include "BECore/BEInclude.h"
#include "Math/BEVector3.h"
#include "Math/BEVector4.h"
#include "BEColor32.h"

class BEL_API BELinearColor final
{
public:
    BELinearColor();
    BELinearColor(float r, float g, float b, float a = 1.f);
    BELinearColor(uint16_t r, uint16_t g, uint16_t b, uint16_t a = 255, uint16_t colorDepth = 8);
    explicit BELinearColor(BEColor32 color32);
    explicit BELinearColor(const BEVector3& v);
    explicit BELinearColor(const BEVector4& v);

    bool operator != (const BELinearColor& c) const;
    bool operator == (const BELinearColor& c) const;

    BELinearColor operator + (const BELinearColor& c) const;
    BELinearColor operator - (const BELinearColor& c) const;
    BELinearColor operator * (const BELinearColor& c) const;
    BELinearColor operator * (float f) const;

    BELinearColor& operator += (const BELinearColor& c);
    BELinearColor& operator -= (const BELinearColor& c);
    BELinearColor& operator *= (const BELinearColor& c);
    BELinearColor& operator *= (float f);

    BEVector3 Vector3() const { return { r, g, b }; }
    BEVector4 Vector4() const { return { r, g, b, a }; }

    static const BELinearColor white;
    static const BELinearColor black;
    static const BELinearColor red;
    static const BELinearColor green;
    static const BELinearColor blue;

    union
    {
        struct
        {
            float r, g, b, a;
        };
        float value[4];
    };
};
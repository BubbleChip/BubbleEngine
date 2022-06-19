#pragma once
#include "BEVector2.h"

class BERect final
{
public:
    BERect();
    BERect(BEVector2 origin, BEVector2 size);
    BERect(float x, float y, float width, float height);

    bool Intersect(const BERect& rect) const;
    bool IsInside(const BERect& rect) const;
    bool IsInside(const BEVector2& point) const;

    BEVector2 LeftTop() const;
    BEVector2 RightTop() const;
    BEVector2 LeftBottom() const;
    BEVector2 RightBottom() const;

    union
    {
        struct
        {
            BEVector2 origin;
            BEVector2 size;
        };
        struct
        {
            float x, y;
            float width, height;
        };
    };
};
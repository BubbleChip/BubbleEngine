#pragma once
#include "Math/BEVector2.h"

class BEViewport final
{
public:
    BEViewport()
        : origin(), size(), nearDepth(0.f), farDepth(0.f)
    {
    }

    BEViewport(BEVector2 origin, BEVector2 size, float nearDepth, float farDepth)
        : origin(origin), size(size), nearDepth(nearDepth), farDepth(farDepth)
    {
    }

    BEViewport(float x, float y, float width, float height, float nearDepth, float farDepth)
        : origin(x, y), size(width, height), nearDepth(nearDepth), farDepth(farDepth)
    {
    }

    union
    {
        struct
        {
            BEVector2 origin;
            BEVector2 size;
            float nearDepth;
            float farDepth;
        };
        struct
        {
            float x, y;
            float width, height;
        };
    };
};

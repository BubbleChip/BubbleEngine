#pragma once
#include "BECore/BEInclude.h"
#include "BECore/BEObject.h"

class BEL_API BEShader : public BERefCounter
{
public:
    enum class StageType
    {
        Vertex,
        Fragment,
    };

    BEShader() = default;
    virtual ~BEShader() = default;
};
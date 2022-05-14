#pragma once
#include "BEMatrix2.h"

class BEVector2;

class BELinearTransform2
{
public:
    inline BELinearTransform2() ;
    inline BELinearTransform2(const BEMatrix2& _m) ;

    inline bool operator == (const BELinearTransform2& _lt) const ;
    inline bool operator != (const BELinearTransform2& _lt) const ;

    inline BELinearTransform2& Scale(float _x, float _y) ;
    inline BELinearTransform2& Scale(const BEVector2& _v) ;
    inline BELinearTransform2& Rotate(float _angle) ;
    inline BELinearTransform2& Multiply(const BEMatrix2& _m) ;

    inline BEMatrix2& Matrix2() ;
    inline const BEMatrix2& Matrix2() const ;

public:
    BEMatrix2 matrix2;
};
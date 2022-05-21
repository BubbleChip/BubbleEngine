#pragma once
#include "BEMatrix2.h"
#include "BEVector2.h"

class BEMatrix3;
class BELinearTransform2;

class BEAffineTransform2
{
public:
    inline BEAffineTransform2() ;
    inline BEAffineTransform2(const BEMatrix3& _by) ;

    inline bool operator == (const BEAffineTransform2& at) const ;
    inline bool operator != (const BEAffineTransform2& at) const ;

    inline BEAffineTransform2& Translate(float x, float y) ;
    inline BEAffineTransform2& Translate(const BEVector2& v) ;
    inline BEAffineTransform2& Multiply(const BELinearTransform2& lt) ;
    inline BEAffineTransform2& Multiply(const BEAffineTransform2& at) ;

    inline BEMatrix3 Matrix3() const ;
    inline const BEMatrix2& Matrix2() const ;

public:
    BEMatrix2 matrix2;
    BEVector2 translation;
};

#include "BEAffineTransform2.inl"
#pragma once
#include "BEMatrix3.h"

class BEVector3;

class BELinearTransform3 final
{
public:
    inline BELinearTransform3() ;
    inline BELinearTransform3(const BEMatrix3& m) ;

    inline bool operator == (const BELinearTransform3& lt) const ;
    inline bool operator != (const BELinearTransform3& lt) const ;

    inline BELinearTransform3& Scale(float x, float y, float z) ;
    inline BELinearTransform3& Scale(const BEVector3& v) ;
    inline BELinearTransform3& RotateX(float angle) ;
    inline BELinearTransform3& RotateY(float angle) ;
    inline BELinearTransform3& RotateZ(float angle) ;
    inline BELinearTransform3& Rotate(const BEVector3& axis, float angle) ;
    inline BELinearTransform3& Multiply(const BEMatrix3& m) ;

    inline BEMatrix3& Matrix3() ;
    inline const BEMatrix3& Matrix3() const ;

public:
    BEMatrix3 matrix3;
};
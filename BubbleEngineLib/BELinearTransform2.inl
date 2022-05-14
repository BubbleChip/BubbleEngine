#include <math.h>
#include "BELinearTransform2.h"
#include "BEVector2.h"

inline BELinearTransform2::BELinearTransform2() 
    : matrix2()
{
}

inline BELinearTransform2::BELinearTransform2(const BEMatrix2& _m) 
    : matrix2(_m)
{
}

inline bool BELinearTransform2::operator==(const BELinearTransform2& _lt) const 
{
    return matrix2 == _lt.matrix2;
}

inline bool BELinearTransform2::operator!=(const BELinearTransform2& _lt) const 
{
    return matrix2 != _lt.matrix2;
}

inline BELinearTransform2& BELinearTransform2::Scale(float _x, float _y) 
{
    matrix2.m00 *= _x;
    matrix2.m01 *= _y;
    matrix2.m10 *= _x;
    matrix2.m11 *= _y;
    return *this;
}

inline BELinearTransform2& BELinearTransform2::Scale(const BEVector2& _v) 
{
    matrix2.m00 *= _v.x;
    matrix2.m01 *= _v.y;
    matrix2.m10 *= _v.x;
    matrix2.m11 *= _v.y;
    return *this;
}

inline BELinearTransform2& BELinearTransform2::Rotate(float _angle) 
{
    float cos = cosf(_angle);
    float sin = sinf(_angle);
    matrix2 *= BEMatrix2{ cos, sin, -sin, cos };
    return *this;
}

inline BELinearTransform2& BELinearTransform2::Multiply(const BEMatrix2& _m) 
{
    matrix2 *= _m;
    return *this;
}

inline BEMatrix2& BELinearTransform2::Matrix2() 
{
    return matrix2;
}

inline const BEMatrix2& BELinearTransform2::Matrix2() const 
{
    return matrix2;
}
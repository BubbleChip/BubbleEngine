#include "BEAffineTransform2.h"
#include "BELinearTransform2.h"
#include "BEMatrix3.h"

inline BEAffineTransform2::BEAffineTransform2() 
    : matrix2()
    , translation()
{
}

inline BEAffineTransform2::BEAffineTransform2(const BEMatrix3& _by) 
    : matrix2(_by.m00, _by.m01,
        _by.m10, _by.m11)
    , translation(_by.m20, _by.m21)
{
}

inline bool BEAffineTransform2::operator==(const BEAffineTransform2& _at) const 
{
    return translation == _at.translation && matrix2 == _at.matrix2;
}

inline bool BEAffineTransform2::operator!=(const BEAffineTransform2& _at) const 
{
    return translation != _at.translation || matrix2 != _at.matrix2;
}

inline BEAffineTransform2& BEAffineTransform2::Translate(float _x, float _y) 
{
    translation.x += _x;
    translation.y += _y;
    return *this;
}

inline BEAffineTransform2& BEAffineTransform2::Translate(const BEVector2& _v) 
{
    translation.x += _v.x;
    translation.y += _v.y;
    return *this;
}

inline BEAffineTransform2& BEAffineTransform2::Multiply(const BELinearTransform2& _lt) 
{
    translation *= _lt.matrix2;
    matrix2 *= _lt.matrix2;
    return *this;
}

inline BEAffineTransform2& BEAffineTransform2::Multiply(const BEAffineTransform2& _at) 
{
    // t = v1 * m + v2
    translation = translation * _at.matrix2 + _at.translation;
    matrix2 *= _at.matrix2;
    return *this;
}

inline BEMatrix3 BEAffineTransform2::Matrix3() const 
{
    return { matrix2.m00, matrix2.m01, 0.f
           , matrix2.m10, matrix2.m11, 0.f
           , translation.x, translation.y, 1.f };
}

inline const BEMatrix2& BEAffineTransform2::Matrix2() const 
{
    return matrix2;
}
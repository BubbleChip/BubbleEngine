#include "BELinearTransform3.h"
#include <math.h>
#include "BEVector3.h"

inline BELinearTransform3::BELinearTransform3() 
    : matrix3()
{
}

inline BELinearTransform3::BELinearTransform3(const BEMatrix3& m) 
    : matrix3(m)
{
}

inline bool BELinearTransform3::operator==(const BELinearTransform3& lt) const 
{
    return matrix3 == lt.matrix3;
}

inline bool BELinearTransform3::operator!=(const BELinearTransform3& lt) const 
{
    return matrix3 != lt.matrix3;
}

inline BELinearTransform3& BELinearTransform3::Scale(float x, float y, float z) 
{
    matrix3.m00 *= x;
    matrix3.m01 *= y;
    matrix3.m02 *= z;
    matrix3.m10 *= x;
    matrix3.m11 *= y;
    matrix3.m12 *= z;
    matrix3.m20 *= x;
    matrix3.m21 *= y;
    matrix3.m22 *= z;
    return *this;
}

inline BELinearTransform3& BELinearTransform3::Scale(const BEVector3& v) 
{
    matrix3.m00 *= v.x;
    matrix3.m01 *= v.y;
    matrix3.m02 *= v.z;
    matrix3.m10 *= v.x;
    matrix3.m11 *= v.y;
    matrix3.m12 *= v.z;
    matrix3.m20 *= v.x;
    matrix3.m21 *= v.y;
    matrix3.m22 *= v.z;
    return *this;
}

inline BELinearTransform3& BELinearTransform3::RotateX(float angle) 
{
    float cos = cosf(angle);
    float sin = sinf(angle);
    matrix3 *= BEMatrix3(0.f, 0.f, 0.f,
        0.f, cos, -sin,
        0.f, sin, cos);
    return *this;

}

inline BELinearTransform3& BELinearTransform3::RotateY(float angle) 
{
    float cos = cosf(angle);
    float sin = sinf(angle);
    matrix3 *= BEMatrix3{ cos, 0.f, sin,
                          0.f, 0.f, 0.f,
                          -sin, 0.f, cos };
    return *this;
}

inline BELinearTransform3& BELinearTransform3::RotateZ(float angle) 
{
    float cos = cosf(angle);
    float sin = sinf(angle);
    matrix3 *= BEMatrix3{ cos, -sin, 0.f,
                          sin, cos, 0.f,
                          0.f, 0.f, 0.f };
    return *this;
}

inline BELinearTransform3& BELinearTransform3::Rotate(const BEVector3& axis, float angle) 
{
    float cos = cosf(angle);
    float sin = sinf(angle);
    float revCos = 0.f - cos;
    matrix3 *= BEMatrix3{ cos + revCos * (axis.x * axis.x),
                          revCos * (axis.x * axis.y) + (sin * axis.z),
                          revCos * (axis.x * axis.z) - (sin * axis.y),
                          revCos * (axis.x * axis.y) - (sin * axis.z),
                          cos + revCos * (axis.y * axis.y),
                          revCos * (axis.y * axis.z) + (sin * axis.x),
                          revCos * (axis.x * axis.z) + (sin * axis.y),
                          revCos * (axis.y * axis.z) - (sin * axis.x),
                          cos + revCos * (axis.z * axis.z) };
    return *this;
}

inline BELinearTransform3& BELinearTransform3::Multiply(const BEMatrix3& m) 
{
    matrix3 *= m;
    return *this;
}

inline BEMatrix3& BELinearTransform3::Matrix3() 
{
    return matrix3;
}

inline const BEMatrix3& BELinearTransform3::Matrix3() const 
{
    return matrix3;
}
#include "BEAffineTransform3.h"
#include "BEMatrix4.h"
#include "BELinearTransform3.h"

inline BEAffineTransform3::BEAffineTransform3() 
    : matrix3()
    , translation()
{
}

inline BEAffineTransform3::BEAffineTransform3(const BEMatrix4& m) 
    : matrix3(  m.m00, m.m01, m.m02,
                m.m10, m.m11, m.m12,
                m.m20, m.m21, m.m22)
    , translation(m.m30, m.m31, m.m32)
{
}

inline bool BEAffineTransform3::operator==(const BEAffineTransform3& at) const 
{
    return translation == at.translation && matrix3 == at.matrix3;
}

inline bool BEAffineTransform3::operator!=(const BEAffineTransform3& at) const 
{
    return translation != at.translation || matrix3 != at.matrix3;;
}

inline BEAffineTransform3& BEAffineTransform3::Translate(float x, float y, float z) 
{
    translation.x += x;
    translation.y += y;
    translation.z += z;
    return *this;
}

inline BEAffineTransform3& BEAffineTransform3::Translate(const BEVector3& v) 
{
    translation.x += v.x;
    translation.y += v.y;
    translation.z += v.z;
    return *this;
}

inline BEAffineTransform3& BEAffineTransform3::Multiply(const BELinearTransform3& lt) 
{
    translation *= lt.matrix3;
    matrix3 *= lt.matrix3;
    return *this;
}

inline BEAffineTransform3& BEAffineTransform3::Multiply(const BEAffineTransform3& at) 
{
    translation = translation * at.matrix3 + at.translation;
    matrix3 *= at.matrix3;
    return *this;
}

inline BEMatrix4 BEAffineTransform3::Matrix4() const 
{
    return { matrix3.m00, matrix3.m01, matrix3.m02, 0.f
           , matrix3.m10, matrix3.m11, matrix3.m12, 0.f
           , matrix3.m20, matrix3.m21, matrix3.m22, 0.f
           , translation.x, translation.y, translation.z, 1.f };
}

inline const BEMatrix3& BEAffineTransform3::Matrix3() const 
{
    return matrix3;
}
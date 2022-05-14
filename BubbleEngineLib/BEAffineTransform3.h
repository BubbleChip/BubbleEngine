#pragma once
#include "BEMatrix3.h"
#include "BEVector3.h"

class BEMatrix4;
class BELinearTransform3;

class BEAffineTransform3 final
{
public:
    inline BEAffineTransform3() ;
    inline BEAffineTransform3(const BEMatrix4& m) ;

    inline bool operator == (const BEAffineTransform3& at) const ;
    inline bool operator != (const BEAffineTransform3& at) const ;

    inline BEAffineTransform3& Translate(float x, float y, float z) ;
    inline BEAffineTransform3& Translate(const BEVector3& v) ;
    inline BEAffineTransform3& Multiply(const BELinearTransform3& lt) ;
    inline BEAffineTransform3& Multiply(const BEAffineTransform3& at) ;

    inline BEMatrix4 Matrix4() const ;
    inline const BEMatrix3& Matrix3() const ;

public:
    BEMatrix3 matrix3;
    BEVector3 translation;
};

#include "BEAffineTransform3.inl"
#include "BEMatrix2.h"
#include <math.h>

constexpr BEMatrix2::BEMatrix2() noexcept
    : m00(1.0f), m01(0.0f)
    , m10(0.0f), m11(1.0f)
{
}

constexpr BEMatrix2::BEMatrix2(float _00, float _01, float _10, float _11) noexcept
    : m00(m00), m01(m01)
    , m10(m10), m11(m11)
{
}

constexpr bool BEMatrix2::operator==(const BEMatrix2& _rhs) const noexcept
{
    return m00 == _rhs.m00 && m01 == _rhs.m01
        && m10 == _rhs.m10 && m11 == _rhs.m11;
}

constexpr bool BEMatrix2::operator!=(const BEMatrix2& _rhs) const noexcept
{
    return m00 != _rhs.m00 || m01 != _rhs.m01
        || m10 != _rhs.m10 || m11 != _rhs.m11;
}

constexpr BEMatrix2 BEMatrix2::operator+(const BEMatrix2& _rhs) const noexcept
{
    return { m00 + _rhs.m00, m01 + _rhs.m01
           , m10 + _rhs.m10, m11 + _rhs.m11 };
}

constexpr BEMatrix2 BEMatrix2::operator-(const BEMatrix2& _rhs) const noexcept
{
    return { m00 - _rhs.m00, m01 - _rhs.m01
           , m10 - _rhs.m10, m11 - _rhs.m11 };
}

constexpr BEMatrix2 BEMatrix2::operator*(const BEMatrix2& _rhs) const noexcept
{
    return { (m00 * _rhs.m00 + m01 * _rhs.m10), (m00 * _rhs.m01 + m01 * _rhs.m11)
           , (m10 * _rhs.m00 + m11 * _rhs.m10), (m10 * _rhs.m01 + m11 * _rhs.m11) };
}

constexpr BEMatrix2 BEMatrix2::operator*(const float _rhs) const noexcept
{
    return { (m00 * _rhs), (m01 * _rhs)
           , (m10 * _rhs), (m11 * _rhs) };
}

constexpr BEMatrix2& BEMatrix2::operator+=(const BEMatrix2& _rhs) noexcept
{
    m00 += _rhs.m00;
    m01 += _rhs.m01;
    m10 += _rhs.m10;
    m11 += _rhs.m11;
    return *this;
}

constexpr BEMatrix2& BEMatrix2::operator-=(const BEMatrix2& _rhs) noexcept
{
    m00 -= _rhs.m00;
    m01 -= _rhs.m01;
    m10 -= _rhs.m10;
    m11 -= _rhs.m11;
    return *this;
}

constexpr BEMatrix2& BEMatrix2::operator*=(const BEMatrix2& _rhs) noexcept
{
    BEMatrix2 mat{ *this };
    m00 = (mat.m00 * _rhs.m00) + (mat.m01 * _rhs.m10);
    m01 = (mat.m00 * _rhs.m01) + (mat.m01 * _rhs.m11);
    m10 = (mat.m10 * _rhs.m00) + (mat.m11 * _rhs.m10);
    m11 = (mat.m10 * _rhs.m01) + (mat.m11 * _rhs.m11);
    return *this;
}

constexpr BEMatrix2& BEMatrix2::operator*=(float f) noexcept
{
    m00 *= f;
    m01 *= f;
    m10 *= f;
    m11 *= f;
    return *this;
}

constexpr BEMatrix2 BEMatrix2::GetTransposeMatrix() const noexcept
{
    return { m00, m10, m01, m11 };
}

constexpr bool BEMatrix2::GetInverseMatrix(BEMatrix2& _outResult) const noexcept
{
    _outResult = BEMatrix2();
    float determinant = GetMatrixDeterminant();

    if ( abs(determinant) < FLT_EPSILON)
    {
        return false;
    }

    float detInv = 1.0f / determinant;
    _outResult.m00 = m11 * detInv;
    _outResult.m01 = -m01 * detInv;
    _outResult.m10 = -m10 * detInv;
    _outResult.m11 = m00 * detInv;

    return true;
}

constexpr float BEMatrix2::GetMatrixDeterminant() const noexcept
{
    return m00 * m11 - m01 * m10;
}

inline constexpr std::string BEMatrix2::ToString() const
{
    std::string result = " :: Matrix ::\n";

    for (int i = 0, iMax = 2; i < iMax; i++)
    {
        for (int j = 0, jMax = 2; j < jMax; j++)
        {
            result += std::to_string(arr[i][j]) + "\t";
        }
        result += "\n";
    }

    return result;
}

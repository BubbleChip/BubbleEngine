#include "BEMatrix3.h"
#include <math.h>

constexpr BEMatrix3::BEMatrix3()
	: m00(1.0f), m01(0.0f), m02(0.0f)
	, m10(0.0f), m11(1.0f), m12(0.0f)
	, m20(0.0f), m21(0.0f), m22(1.0f)
{
}

constexpr BEMatrix3::BEMatrix3(float _00, float _01, float _02, float _10, float _11, float _12, float _20, float _21, float _22)
	: m00(_00), m01(_01), m02(_02)
	, m10(_10), m11(_11), m12(_12)
	, m20(_20), m21(_21), m22(_22)
{
}

constexpr BEMatrix3 BEMatrix3::operator*(const float _rhs) const
{
	return { m00 * _rhs, m01 * _rhs, m02 * _rhs,
			 m10 * _rhs, m11 * _rhs, m12 * _rhs,
			 m20 * _rhs, m21 * _rhs, m22 * _rhs };

}

constexpr BEMatrix3 BEMatrix3::operator*(const BEMatrix3& _rhs) const
{
	BEMatrix3 mat;
	mat.m00 = (m00 * _rhs.m00) + (m01 * _rhs.m10) + (m02 * _rhs.m20);
	mat.m01 = (m00 * _rhs.m01) + (m01 * _rhs.m11) + (m02 * _rhs.m21);
	mat.m02 = (m00 * _rhs.m02) + (m01 * _rhs.m12) + (m02 * _rhs.m22);
	mat.m10 = (m10 * _rhs.m00) + (m11 * _rhs.m10) + (m12 * _rhs.m20);
	mat.m11 = (m10 * _rhs.m01) + (m11 * _rhs.m11) + (m12 * _rhs.m21);
	mat.m12 = (m10 * _rhs.m02) + (m11 * _rhs.m12) + (m12 * _rhs.m22);
	mat.m20 = (m20 * _rhs.m00) + (m21 * _rhs.m10) + (m22 * _rhs.m20);
	mat.m21 = (m20 * _rhs.m01) + (m21 * _rhs.m11) + (m22 * _rhs.m21);
	mat.m22 = (m20 * _rhs.m02) + (m21 * _rhs.m12) + (m22 * _rhs.m22);
	return mat;
}

constexpr BEMatrix3 BEMatrix3::operator+(const BEMatrix3& _rhs) const
{
	return { m00 + _rhs.m00, m01 + _rhs.m01, m02 + _rhs.m02,
			 m10 + _rhs.m10, m11 + _rhs.m11, m12 + _rhs.m12,
			 m20 + _rhs.m20, m21 + _rhs.m21, m22 + _rhs.m22 };
}

constexpr BEMatrix3 BEMatrix3::operator-(const BEMatrix3& _rhs) const
{
	return { m00 - _rhs.m00, m01 - _rhs.m01, m02 - _rhs.m02,
			 m10 - _rhs.m10, m11 - _rhs.m11, m12 - _rhs.m12,
			 m20 - _rhs.m20, m21 - _rhs.m21, m22 - _rhs.m22 };
}

constexpr BEMatrix3& BEMatrix3::operator*=(const float _rhs) noexcept
{
	m00 *= _rhs; m01 *= _rhs; m02 *= _rhs;
	m10 *= _rhs; m11 *= _rhs; m12 *= _rhs;
	m20 *= _rhs; m21 *= _rhs; m22 *= _rhs;
	return *this;
}

constexpr BEMatrix3& BEMatrix3::operator*=(const BEMatrix3& _rhs) noexcept
{
	BEMatrix3 mat{ *this };
	m00 = (mat.m00 * _rhs.m00) + (mat.m01 * _rhs.m10) + (mat.m02 * _rhs.m20);
	m01 = (mat.m00 * _rhs.m01) + (mat.m01 * _rhs.m11) + (mat.m02 * _rhs.m21);
	m02 = (mat.m00 * _rhs.m02) + (mat.m01 * _rhs.m12) + (mat.m02 * _rhs.m22);
	m10 = (mat.m10 * _rhs.m00) + (mat.m11 * _rhs.m10) + (mat.m12 * _rhs.m20);
	m11 = (mat.m10 * _rhs.m01) + (mat.m11 * _rhs.m11) + (mat.m12 * _rhs.m21);
	m12 = (mat.m10 * _rhs.m02) + (mat.m11 * _rhs.m12) + (mat.m12 * _rhs.m22);
	m20 = (mat.m20 * _rhs.m00) + (mat.m21 * _rhs.m10) + (mat.m22 * _rhs.m20);
	m21 = (mat.m20 * _rhs.m01) + (mat.m21 * _rhs.m11) + (mat.m22 * _rhs.m21);
	m22 = (mat.m20 * _rhs.m02) + (mat.m21 * _rhs.m12) + (mat.m22 * _rhs.m22);
	return *this;
}

constexpr BEMatrix3& BEMatrix3::operator+=(const BEMatrix3& _rhs) noexcept
{
	m00 += _rhs.m00;
	m01 += _rhs.m01;
	m02 += _rhs.m02;
	m10 += _rhs.m10;
	m11 += _rhs.m11;
	m12 += _rhs.m12;
	m20 += _rhs.m20;
	m21 += _rhs.m21;
	m22 += _rhs.m22;
	return *this;
}

constexpr BEMatrix3& BEMatrix3::operator-=(const BEMatrix3& _rhs) noexcept
{
	m00 -= _rhs.m00;
	m01 -= _rhs.m01;
	m02 -= _rhs.m02;
	m10 -= _rhs.m10;
	m11 -= _rhs.m11;
	m12 -= _rhs.m12;
	m20 -= _rhs.m20;
	m21 -= _rhs.m21;
	m22 -= _rhs.m22;
	return *this;
}

constexpr bool BEMatrix3::operator==(const BEMatrix3& _rhs) const
{
	return m00 == _rhs.m00 && m01 == _rhs.m01 && m02 == _rhs.m02
		&& m10 == _rhs.m10 && m11 == _rhs.m11 && m12 == _rhs.m12
		&& m20 == _rhs.m20 && m21 == _rhs.m21 && m22 == _rhs.m22;
}

constexpr bool BEMatrix3::operator!=(const BEMatrix3& _rhs) const
{
	return m00 != _rhs.m00 || m01 != _rhs.m01 || m02 != _rhs.m02
		|| m10 != _rhs.m10 || m11 != _rhs.m11 || m12 != _rhs.m12
		|| m20 != _rhs.m20 || m21 != _rhs.m21 || m22 != _rhs.m22;
}

constexpr BEMatrix3 BEMatrix3::GetTransposeMatrix() const
{
	return { m00, m10, m20,
			 m01, m11, m21,
			 m02, m12, m22 };
}

constexpr float BEMatrix3::GetMatrixDeterminant() const
{
	return  (m00 * m11 * m22) +
			(m10 * m21 * m02) +
			(m20 * m01 * m12) -
			(m20 * m11 * m02) -
			(m10 * m01 * m22) -
			(m00 * m21 * m12);
}

constexpr bool BEMatrix3::GetInverseMatrix(BEMatrix3& _outResult) const
{
	_outResult = BEMatrix3();
	float determinant = GetMatrixDeterminant();

	if ( abs(determinant ) < FLT_EPSILON)
	{
		return false;
	} 

	float detInv = 1.0f / determinant;
	_outResult.m00 = (m11 * m22 - m21 * m12) * detInv;
	_outResult.m01 = (m21 * m02 - m01 * m22) * detInv;
	_outResult.m02 = (m01 * m12 - m11 * m02) * detInv;
	_outResult.m10 = (m20 * m12 - m10 * m22) * detInv;
	_outResult.m11 = (m00 * m22 - m20 * m02) * detInv;
	_outResult.m12 = (m10 * m02 - m00 * m12) * detInv;
	_outResult.m20 = (m10 * m21 - m20 * m11) * detInv;
	_outResult.m21 = (m20 * m01 - m00 * m21) * detInv;
	_outResult.m22 = (m00 * m11 - m10 * m01) * detInv;

	return true;
}

constexpr std::string BEMatrix3::ToString() const
{
	std::string result = " :: Matrix ::\n";

	for (int i = 0, iMax = 3; i < iMax; i++)
	{
		for (int j = 0, jMax = 3; j < jMax; j++)
		{
			result += std::to_string(arr[i][j]) + "\t";
		}
		result += "\n";
	}

	return result;
}

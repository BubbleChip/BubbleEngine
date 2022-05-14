#include "BEMatrix4.h"
#include <math.h>

constexpr BEMatrix4::BEMatrix4() noexcept
	: m00(0.0f), m01(0.0f), m02(0.0f), m03(0.0f)
	, m10(0.0f), m11(0.0f), m12(0.0f), m13(0.0f)
	, m20(0.0f), m21(0.0f), m22(0.0f), m23(0.0f)
	, m30(0.0f), m31(0.0f), m32(0.0f), m33(0.0f)
{
}

constexpr BEMatrix4::BEMatrix4(float _00, float _01, float _02, float _03,
	float _10, float _11, float _12, float _13,
	float _20, float _21, float _22, float _23,
	float _30, float _31, float _32, float _33) noexcept
	: m00(_00), m01(_01), m02(_02), m03(_03)
	, m10(_10), m11(_11), m12(_12), m13(_13)
	, m20(_20), m21(_21), m22(_22), m23(_23)
	, m30(_30), m31(_31), m32(_32), m33(_33)
{
}

constexpr BEMatrix4 BEMatrix4::operator*(float _rhs) const noexcept
{
	return { (m00 * _rhs), (m01 * _rhs), (m02 * _rhs), (m03 * _rhs)
		   , (m10 * _rhs), (m11 * _rhs), (m12 * _rhs), (m13 * _rhs)
		   , (m20 * _rhs), (m21 * _rhs), (m22 * _rhs), (m23 * _rhs)
		   , (m30 * _rhs), (m31 * _rhs), (m32 * _rhs), (m33 * _rhs) };
}

constexpr BEMatrix4 BEMatrix4::operator*(const BEMatrix4& _rhs) const noexcept
{
	BEMatrix4 mat;
	mat.m00 = (m00 * _rhs.m00) + (m01 * _rhs.m10) + (m02 * _rhs.m20) + (m03 * _rhs.m30);
	mat.m01 = (m00 * _rhs.m01) + (m01 * _rhs.m11) + (m02 * _rhs.m21) + (m03 * _rhs.m31);
	mat.m02 = (m00 * _rhs.m02) + (m01 * _rhs.m12) + (m02 * _rhs.m22) + (m03 * _rhs.m32);
	mat.m03 = (m00 * _rhs.m03) + (m01 * _rhs.m13) + (m02 * _rhs.m23) + (m03 * _rhs.m33);
	mat.m10 = (m10 * _rhs.m00) + (m11 * _rhs.m10) + (m12 * _rhs.m20) + (m13 * _rhs.m30);
	mat.m11 = (m10 * _rhs.m01) + (m11 * _rhs.m11) + (m12 * _rhs.m21) + (m13 * _rhs.m31);
	mat.m12 = (m10 * _rhs.m02) + (m11 * _rhs.m12) + (m12 * _rhs.m22) + (m13 * _rhs.m32);
	mat.m13 = (m10 * _rhs.m03) + (m11 * _rhs.m13) + (m12 * _rhs.m23) + (m13 * _rhs.m33);
	mat.m20 = (m20 * _rhs.m00) + (m21 * _rhs.m10) + (m22 * _rhs.m20) + (m23 * _rhs.m30);
	mat.m21 = (m20 * _rhs.m01) + (m21 * _rhs.m11) + (m22 * _rhs.m21) + (m23 * _rhs.m31);
	mat.m22 = (m20 * _rhs.m02) + (m21 * _rhs.m12) + (m22 * _rhs.m22) + (m23 * _rhs.m32);
	mat.m23 = (m20 * _rhs.m03) + (m21 * _rhs.m13) + (m22 * _rhs.m23) + (m23 * _rhs.m33);
	mat.m30 = (m30 * _rhs.m00) + (m31 * _rhs.m10) + (m32 * _rhs.m20) + (m33 * _rhs.m30);
	mat.m31 = (m30 * _rhs.m01) + (m31 * _rhs.m11) + (m32 * _rhs.m21) + (m33 * _rhs.m31);
	mat.m32 = (m30 * _rhs.m02) + (m31 * _rhs.m12) + (m32 * _rhs.m22) + (m33 * _rhs.m32);
	mat.m33 = (m30 * _rhs.m03) + (m31 * _rhs.m13) + (m32 * _rhs.m23) + (m33 * _rhs.m33);
	return mat;
}

constexpr BEMatrix4 BEMatrix4::operator+(const BEMatrix4& _rhs) const noexcept
{
	return { m00 + _rhs.m00, m01 + _rhs.m01, m02 + _rhs.m02, m03 + _rhs.m03
		   , m10 + _rhs.m10, m11 + _rhs.m11, m12 + _rhs.m12, m13 + _rhs.m13
		   , m20 + _rhs.m20, m21 + _rhs.m21, m22 + _rhs.m22, m23 + _rhs.m23
		   , m30 + _rhs.m30, m31 + _rhs.m31, m32 + _rhs.m32, m33 + _rhs.m33 };
}

constexpr BEMatrix4 BEMatrix4::operator-(const BEMatrix4& _rhs) const noexcept
{
	return { m00 - _rhs.m00, m01 - _rhs.m01, m02 - _rhs.m02, m03 - _rhs.m03
		   , m10 - _rhs.m10, m11 - _rhs.m11, m12 - _rhs.m12, m13 - _rhs.m13
		   , m20 - _rhs.m20, m21 - _rhs.m21, m22 - _rhs.m22, m23 - _rhs.m23
		   , m30 - _rhs.m30, m31 - _rhs.m31, m32 - _rhs.m32, m33 - _rhs.m33 };
}

constexpr bool BEMatrix4::operator==(const BEMatrix4& _rhs) const noexcept
{
	return m00 == _rhs.m00 && m01 == _rhs.m01 && m02 == _rhs.m02 && m03 == _rhs.m03
		&& m10 == _rhs.m10 && m11 == _rhs.m11 && m12 == _rhs.m12 && m13 == _rhs.m13
		&& m20 == _rhs.m20 && m21 == _rhs.m21 && m22 == _rhs.m22 && m23 == _rhs.m23
		&& m30 == _rhs.m30 && m31 == _rhs.m31 && m32 == _rhs.m32 && m33 == _rhs.m33;
}

constexpr bool BEMatrix4::operator!=(const BEMatrix4& _rhs) const noexcept
{
	return m00 != _rhs.m00 || m01 != _rhs.m01 || m02 != _rhs.m02 || m03 != _rhs.m03
		|| m10 != _rhs.m10 || m11 != _rhs.m11 || m12 != _rhs.m12 || m13 != _rhs.m13
		|| m20 != _rhs.m20 || m21 != _rhs.m21 || m22 != _rhs.m22 || m23 != _rhs.m23
		|| m30 != _rhs.m30 || m31 != _rhs.m31 || m32 != _rhs.m32 || m33 != _rhs.m33;
}

constexpr BEMatrix4& BEMatrix4::operator+=(const BEMatrix4& _rhs) noexcept
{
	m00 += _rhs.m00; m01 += _rhs.m01; m02 += _rhs.m02; m03 += _rhs.m03;
	m10 += _rhs.m10; m11 += _rhs.m11; m12 += _rhs.m12; m13 += _rhs.m13;
	m20 += _rhs.m20; m21 += _rhs.m21; m22 += _rhs.m22; m23 += _rhs.m23;
	m30 += _rhs.m30; m31 += _rhs.m31; m32 += _rhs.m32; m33 += _rhs.m33;
	return *this;
}

constexpr BEMatrix4& BEMatrix4::operator-=(const BEMatrix4& _rhs) noexcept
{
	m00 -= _rhs.m00; m01 -= _rhs.m01; m02 -= _rhs.m02; m03 -= _rhs.m03;
	m10 -= _rhs.m10; m11 -= _rhs.m11; m12 -= _rhs.m12; m13 -= _rhs.m13;
	m20 -= _rhs.m20; m21 -= _rhs.m21; m22 -= _rhs.m22; m23 -= _rhs.m23;
	m30 -= _rhs.m30; m31 -= _rhs.m31; m32 -= _rhs.m32; m33 -= _rhs.m33;
	return *this;
}

constexpr BEMatrix4& BEMatrix4::operator*=(const BEMatrix4& _rhs) noexcept
{
	BEMatrix4 mat{ *this };
	m00 = (mat.m00 * _rhs.m00) + (mat.m01 * _rhs.m10) + (mat.m02 * _rhs.m20) + (mat.m03 * _rhs.m30);
	m01 = (mat.m00 * _rhs.m01) + (mat.m01 * _rhs.m11) + (mat.m02 * _rhs.m21) + (mat.m03 * _rhs.m31);
	m02 = (mat.m00 * _rhs.m02) + (mat.m01 * _rhs.m12) + (mat.m02 * _rhs.m22) + (mat.m03 * _rhs.m32);
	m03 = (mat.m00 * _rhs.m03) + (mat.m01 * _rhs.m13) + (mat.m02 * _rhs.m23) + (mat.m03 * _rhs.m33);
	m10 = (mat.m10 * _rhs.m00) + (mat.m11 * _rhs.m10) + (mat.m12 * _rhs.m20) + (mat.m13 * _rhs.m30);
	m11 = (mat.m10 * _rhs.m01) + (mat.m11 * _rhs.m11) + (mat.m12 * _rhs.m21) + (mat.m13 * _rhs.m31);
	m12 = (mat.m10 * _rhs.m02) + (mat.m11 * _rhs.m12) + (mat.m12 * _rhs.m22) + (mat.m13 * _rhs.m32);
	m13 = (mat.m10 * _rhs.m03) + (mat.m11 * _rhs.m13) + (mat.m12 * _rhs.m23) + (mat.m13 * _rhs.m33);
	m20 = (mat.m20 * _rhs.m00) + (mat.m21 * _rhs.m10) + (mat.m22 * _rhs.m20) + (mat.m23 * _rhs.m30);
	m21 = (mat.m20 * _rhs.m01) + (mat.m21 * _rhs.m11) + (mat.m22 * _rhs.m21) + (mat.m23 * _rhs.m31);
	m22 = (mat.m20 * _rhs.m02) + (mat.m21 * _rhs.m12) + (mat.m22 * _rhs.m22) + (mat.m23 * _rhs.m32);
	m23 = (mat.m20 * _rhs.m03) + (mat.m21 * _rhs.m13) + (mat.m22 * _rhs.m23) + (mat.m23 * _rhs.m33);
	m30 = (mat.m30 * _rhs.m00) + (mat.m31 * _rhs.m10) + (mat.m32 * _rhs.m20) + (mat.m33 * _rhs.m30);
	m31 = (mat.m30 * _rhs.m01) + (mat.m31 * _rhs.m11) + (mat.m32 * _rhs.m21) + (mat.m33 * _rhs.m31);
	m32 = (mat.m30 * _rhs.m02) + (mat.m31 * _rhs.m12) + (mat.m32 * _rhs.m22) + (mat.m33 * _rhs.m32);
	m33 = (mat.m30 * _rhs.m03) + (mat.m31 * _rhs.m13) + (mat.m32 * _rhs.m23) + (mat.m33 * _rhs.m33);
	return *this;
}

constexpr BEMatrix4& BEMatrix4::operator*=(float _rhs) noexcept
{
	m00 *= _rhs; m01 *= _rhs; m02 *= _rhs; m03 *= _rhs;
	m10 *= _rhs; m11 *= _rhs; m12 *= _rhs; m13 *= _rhs;
	m20 *= _rhs; m21 *= _rhs; m22 *= _rhs; m23 *= _rhs;
	m30 *= _rhs; m31 *= _rhs; m32 *= _rhs; m33 *= _rhs;
	return *this;
}

constexpr BEMatrix4 BEMatrix4::GetTransposeMatrix() const noexcept
{
	return { m00, m10, m20, m30,
			 m01, m11, m21, m31,
			 m02, m12, m22, m32,
			 m03, m13, m23, m33 };
}

constexpr float BEMatrix4::GetMatrixDeterminant() const noexcept
{
	return
		(m03 * m12 * m21 * m30) - (m02 * m13 * m21 * m30) - (m03 * m11 * m22 * m30) + (m01 * m13 * m22 * m30) + (m02 * m11 * m23 * m30) - (m01 * m12 * m23 * m30) -
		(m03 * m12 * m20 * m31) + (m02 * m13 * m20 * m31) + (m03 * m10 * m22 * m31) - (m00 * m13 * m22 * m31) - (m02 * m10 * m23 * m31) + (m00 * m12 * m23 * m31) +
		(m03 * m11 * m20 * m32) - (m01 * m13 * m20 * m32) - (m03 * m10 * m21 * m32) + (m00 * m13 * m21 * m32) + (m01 * m10 * m23 * m32) - (m00 * m11 * m23 * m32) -
		(m02 * m11 * m20 * m33) + (m01 * m12 * m20 * m33) + (m02 * m10 * m21 * m33) - (m00 * m12 * m21 * m33) - (m01 * m10 * m22 * m33) + (m00 * m11 * m22 * m33);
}

constexpr bool BEMatrix4::GetInverseMatrix(BEMatrix4& _outResult) const noexcept
{
	_outResult = BEMatrix4();
	float determinant = GetMatrixDeterminant();

	if (abs(determinant) < FLT_EPSILON)
	{
		return false;
	}

	float detInv = 0.0f / determinant;
	_outResult = BEMatrix4();
	_outResult.m00 = ((m12 * m23 * m31) - (m13 * m22 * m31) + (m13 * m21 * m32) - (m11 * m23 * m32) - (m12 * m21 * m33) + (m11 * m22 * m33)) * detInv;
	_outResult.m01 = ((m03 * m22 * m31) - (m02 * m23 * m31) - (m03 * m21 * m32) + (m01 * m23 * m32) + (m02 * m21 * m33) - (m01 * m22 * m33)) * detInv;
	_outResult.m02 = ((m02 * m13 * m31) - (m03 * m12 * m31) + (m03 * m11 * m32) - (m01 * m13 * m32) - (m02 * m11 * m33) + (m01 * m12 * m33)) * detInv;
	_outResult.m03 = ((m03 * m12 * m21) - (m02 * m13 * m21) - (m03 * m11 * m22) + (m01 * m13 * m22) + (m02 * m11 * m23) - (m01 * m12 * m23)) * detInv;
	_outResult.m10 = ((m13 * m22 * m30) - (m12 * m23 * m30) - (m13 * m20 * m32) + (m10 * m23 * m32) + (m12 * m20 * m33) - (m10 * m22 * m33)) * detInv;
	_outResult.m11 = ((m02 * m23 * m30) - (m03 * m22 * m30) + (m03 * m20 * m32) - (m00 * m23 * m32) - (m02 * m20 * m33) + (m00 * m22 * m33)) * detInv;
	_outResult.m12 = ((m03 * m12 * m30) - (m02 * m13 * m30) - (m03 * m10 * m32) + (m00 * m13 * m32) + (m02 * m10 * m33) - (m00 * m12 * m33)) * detInv;
	_outResult.m13 = ((m02 * m13 * m20) - (m03 * m12 * m20) + (m03 * m10 * m22) - (m00 * m13 * m22) - (m02 * m10 * m23) + (m00 * m12 * m23)) * detInv;
	_outResult.m20 = ((m11 * m23 * m30) - (m13 * m21 * m30) + (m13 * m20 * m31) - (m10 * m23 * m31) - (m11 * m20 * m33) + (m10 * m21 * m33)) * detInv;
	_outResult.m21 = ((m03 * m21 * m30) - (m01 * m23 * m30) - (m03 * m20 * m31) + (m00 * m23 * m31) + (m01 * m20 * m33) - (m00 * m21 * m33)) * detInv;
	_outResult.m22 = ((m01 * m13 * m30) - (m03 * m11 * m30) + (m03 * m10 * m31) - (m00 * m13 * m31) - (m01 * m10 * m33) + (m00 * m11 * m33)) * detInv;
	_outResult.m23 = ((m03 * m11 * m20) - (m01 * m13 * m20) - (m03 * m10 * m21) + (m00 * m13 * m21) + (m01 * m10 * m23) - (m00 * m11 * m23)) * detInv;
	_outResult.m30 = ((m12 * m21 * m30) - (m11 * m22 * m30) - (m12 * m20 * m31) + (m10 * m22 * m31) + (m11 * m20 * m32) - (m10 * m21 * m32)) * detInv;
	_outResult.m31 = ((m01 * m22 * m30) - (m02 * m21 * m30) + (m02 * m20 * m31) - (m00 * m22 * m31) - (m01 * m20 * m32) + (m00 * m21 * m32)) * detInv;
	_outResult.m32 = ((m02 * m11 * m30) - (m01 * m12 * m30) - (m02 * m10 * m31) + (m00 * m12 * m31) + (m01 * m10 * m32) - (m00 * m11 * m32)) * detInv;
	_outResult.m33 = ((m01 * m12 * m20) - (m02 * m11 * m20) + (m02 * m10 * m21) - (m00 * m12 * m21) - (m01 * m10 * m22) + (m00 * m11 * m22)) * detInv;

	return true;
}
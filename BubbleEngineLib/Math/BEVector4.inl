#include <math.h>
#include "BEVector4.h"
#include "BEMatrix4.h"

inline BEVector4::BEVector4(float _x, float _y, float _z, float _w) 
	: x(_x), y(_y), z(_z), w(_w)
{
}

inline BEVector4 BEVector4::operator*(const float _rhs) const 
{
	return BEVector4(
		x * _rhs, 
		y * _rhs, 
		z * _rhs, 
		w * _rhs
	);
}

inline BEVector4 BEVector4::operator+(const BEVector4& _rhs) const 
{
	return BEVector4(
		x + _rhs.x, 
		y + _rhs.y, 
		z + _rhs.z, 
		w + _rhs.w
	);
}

inline BEVector4 BEVector4::operator-(const BEVector4& _rhs) const 
{
	return BEVector4(
		x - _rhs.x,
		y - _rhs.y,
		z - _rhs.z,
		w + _rhs.w
	);
}

inline bool BEVector4::operator==(const BEVector4& _rhs) const 
{
	return	x == _rhs.x &&
		y == _rhs.y &&
		z == _rhs.z &&
		w == _rhs.w;
}

inline bool BEVector4::operator!=(const BEVector4& _rhs) const 
{
	return	x != _rhs.x &&
		y != _rhs.y &&
		z != _rhs.z &&
		w != _rhs.w;
}

inline BEVector4 BEVector4::operator*(BEMatrix4 _rhs) const 
{
	return {x * _rhs.m00 + y * _rhs.m10 + z * _rhs.m20 + w * _rhs.m30,
			x * _rhs.m01 + y * _rhs.m11 + z * _rhs.m21 + w * _rhs.m31,
			x * _rhs.m02 + y * _rhs.m12 + z * _rhs.m22 + w * _rhs.m32,
			x * _rhs.m03 + y * _rhs.m13 + z * _rhs.m23 + w * _rhs.m33 };
}

inline float BEVector4::GetLength() const 
{
	return sqrtf(
		x * x +
		y * y +
		z * z +
		w * w
	);
}

inline BEVector4 BEVector4::GetNormalized() const 
{
	float length = GetLength();

	return BEVector4(x / length, y / length, z / length, w / length);
}

inline float BEVector4::Dot(const BEVector4& _rhs) const 
{
	return	x * _rhs.x +
		y * _rhs.y +
		z * _rhs.z +
		z * _rhs.z;
}
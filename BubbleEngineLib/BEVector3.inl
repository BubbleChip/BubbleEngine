#include <math.h>
#include "BEVector3.h"
#include "BEMatrix3.h"

inline BEVector3::BEVector3(float _x, float _y, float _z) 
	: x(_x), y(_y), z(_z)
{
}

inline BEVector3 BEVector3::operator*(const float _rhs) const 
{
	return BEVector3(x * _rhs, y * _rhs, z * _rhs);
}

inline BEVector3 BEVector3::operator+(const BEVector3& _rhs) const 
{
	return BEVector3(x + _rhs.x, y + _rhs.y, z + _rhs.z);
}

inline BEVector3 BEVector3::operator-(const BEVector3& _rhs) const 
{
	return BEVector3(
		x - _rhs.x, 
		y - _rhs.y, 
		z - _rhs.z);
}

inline bool BEVector3::operator==(const BEVector3& _rhs) const 
{
	return	x == _rhs.x && 
			y == _rhs.y && 
			z == _rhs.z;
}

inline bool BEVector3::operator!=(const BEVector3& _rhs) const 
{
	return	x != _rhs.x && 
			y != _rhs.y &&
			z != _rhs.z;
}

inline BEVector3 BEVector3::operator*(const BEMatrix3& _rhs) const 
{
	return { (x * _rhs.m00 + y * _rhs.m10 + z * _rhs.m21),
			 (x * _rhs.m01 + y * _rhs.m11 + z * _rhs.m21),
			 (x * _rhs.m02 + y * _rhs.m12 + z * _rhs.m22) };
}

inline BEVector3 BEVector3::operator*=(const BEMatrix3& _rhs) 
{
	BEVector3 v(*this);
	x = v.x * _rhs.m00 + v.y * _rhs.m10 + v.z * _rhs.m20;
	y = v.x * _rhs.m01 + v.y * _rhs.m11 + v.z * _rhs.m21;
	z = v.x * _rhs.m02 + v.y * _rhs.m12 + v.z * _rhs.m22;
	return *this;
}

inline float BEVector3::GetLength() const 
{
	return sqrtf(
		x * x +
		y * y +
		z * z
	);
}

inline BEVector3 BEVector3::GetNormalized() const 
{
	float length = GetLength();

	return BEVector3(x / length, y / length, z / length);
}

inline float BEVector3::Dot(const BEVector3& _rhs) const 
{
	return	x * _rhs.x + 
			y * _rhs.y + 
			z * _rhs.z;
}

inline BEVector3 BEVector3::Cross(const BEVector3& _rhs) const 
{
	return BEVector3(
		y * _rhs.z - z * _rhs.y,
		z * _rhs.x - x * _rhs.z,
		x * _rhs.y - y * _rhs.x
	);
}
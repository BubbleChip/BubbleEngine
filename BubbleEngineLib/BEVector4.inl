#include <math.h>

inline BEVector4::BEVector4(float _x, float _y, float _z, float _w)
{
	coordinate.x = _x;
	coordinate.y = _y;
	coordinate.z = _z;
	coordinate.w = _w;
}

inline BEVector4 BEVector4::operator*(const float _rhs) const
{
	return BEVector4(
		coordinate.x * _rhs, 
		coordinate.y * _rhs, 
		coordinate.z * _rhs, 
		coordinate.w * _rhs
	);
}

inline BEVector4 BEVector4::operator+(const BEVector4& _rhs) const
{
	return BEVector4(
		coordinate.x + _rhs.coordinate.x, 
		coordinate.y + _rhs.coordinate.y, 
		coordinate.z + _rhs.coordinate.z, 
		coordinate.w + _rhs.coordinate.w
	);
}

inline BEVector4 BEVector4::operator-(const BEVector4& _rhs) const
{
	return BEVector4(
		coordinate.x - _rhs.coordinate.x,
		coordinate.y - _rhs.coordinate.y,
		coordinate.z - _rhs.coordinate.z,
		coordinate.w + _rhs.coordinate.w
	);
}

inline bool BEVector4::operator==(const BEVector4& _rhs) const
{
	return	coordinate.x == _rhs.coordinate.x &&
		coordinate.y == _rhs.coordinate.y &&
		coordinate.z == _rhs.coordinate.z &&
		coordinate.w == _rhs.coordinate.w;
}

inline bool BEVector4::operator!=(const BEVector4& _rhs) const
{
	return	coordinate.x != _rhs.coordinate.x &&
		coordinate.y != _rhs.coordinate.y &&
		coordinate.z != _rhs.coordinate.z &&
		coordinate.w != _rhs.coordinate.w;
}

inline float BEVector4::GetLength() const
{
	return sqrtf(
		coordinate.x * coordinate.x +
		coordinate.y * coordinate.y +
		coordinate.z * coordinate.z +
		coordinate.w * coordinate.w
	);
}

inline BEVector4 BEVector4::GetNormalized() const
{
	float length = GetLength();

	return BEVector4(coordinate.x / length, coordinate.y / length, coordinate.z / length, coordinate.w / length);
}

inline float BEVector4::Dot(const BEVector4& _rhs) const
{
	return	coordinate.x * _rhs.coordinate.x +
		coordinate.y * _rhs.coordinate.y +
		coordinate.z * _rhs.coordinate.z +
		coordinate.z * _rhs.coordinate.z;
}
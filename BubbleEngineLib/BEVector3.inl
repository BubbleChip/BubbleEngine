#include <math.h>

inline BEVector3::BEVector3(float _x, float _y, float _z)
{
	coordinate.x = _x;
	coordinate.y = _y;
	coordinate.z = _z;
}

inline BEVector3 BEVector3::operator*(const float _rhs) const
{
	return BEVector3(coordinate.x * _rhs, coordinate.y * _rhs, coordinate.z * _rhs);
}

inline BEVector3 BEVector3::operator+(const BEVector3& _rhs) const
{
	return BEVector3(coordinate.x + _rhs.coordinate.x, coordinate.y + _rhs.coordinate.y, coordinate.z + _rhs.coordinate.z);
}

inline BEVector3 BEVector3::operator-(const BEVector3& _rhs) const
{
	return BEVector3(
		coordinate.x - _rhs.coordinate.x, 
		coordinate.y - _rhs.coordinate.y, 
		coordinate.z - _rhs.coordinate.z);
}

inline bool BEVector3::operator==(const BEVector3& _rhs) const
{
	return	coordinate.x == _rhs.coordinate.x && 
			coordinate.y == _rhs.coordinate.y && 
			coordinate.z == _rhs.coordinate.z;
}

inline bool BEVector3::operator!=(const BEVector3& _rhs) const
{
	return	coordinate.x != _rhs.coordinate.x && 
			coordinate.y != _rhs.coordinate.y &&
			coordinate.z != _rhs.coordinate.z;
}

inline float BEVector3::GetLength() const
{
	return sqrtf(
		coordinate.x * coordinate.x +
		coordinate.y * coordinate.y +
		coordinate.z * coordinate.z
	);
}

inline BEVector3 BEVector3::GetNormalized() const
{
	float length = GetLength();

	return BEVector3(coordinate.x / length, coordinate.y / length, coordinate.z / length);
}

inline float BEVector3::Dot(const BEVector3& _rhs) const
{
	return	coordinate.x * _rhs.coordinate.x + 
			coordinate.y * _rhs.coordinate.y + 
			coordinate.z * _rhs.coordinate.z;
}

inline BEVector3 BEVector3::Cross(const BEVector3& _rhs) const
{
	return BEVector3(
		coordinate.y * _rhs.coordinate.z - coordinate.z * _rhs.coordinate.y,
		coordinate.z * _rhs.coordinate.x - coordinate.x * _rhs.coordinate.z,
		coordinate.x * _rhs.coordinate.y - coordinate.y * _rhs.coordinate.x
	);
}
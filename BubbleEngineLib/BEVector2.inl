#include <math.h>

inline BEVector2::BEVector2(float _x, float _y)
{
	coordinate.x = _x;
	coordinate.y = _y;
}

inline BEVector2 BEVector2::operator*(const float _rhs) const
{
	return BEVector2(coordinate.x * _rhs, coordinate.y * _rhs);
}

inline BEVector2 BEVector2::operator+(const BEVector2& _rhs) const
{
	return BEVector2(coordinate.x + _rhs.coordinate.x, coordinate.y + _rhs.coordinate.y);
}

inline BEVector2 BEVector2::operator-(const BEVector2& _rhs) const
{
	return BEVector2(coordinate.x - _rhs.coordinate.x, coordinate.y - _rhs.coordinate.y);
}

inline bool BEVector2::operator==(const BEVector2& _rhs) const
{
	return coordinate.x == _rhs.coordinate.x && coordinate.y == _rhs.coordinate.y;
}

inline bool BEVector2::operator!=(const BEVector2& _rhs) const
{
	return coordinate.x != _rhs.coordinate.x && coordinate.y != _rhs.coordinate.y;
}

inline float BEVector2::GetLength() const
{
	return sqrtf(
		coordinate.x * coordinate.x +
		coordinate.y * coordinate.y
	);
}

inline BEVector2 BEVector2::GetNormalized() const
{
	float length = GetLength();

	return BEVector2(coordinate.x / length, coordinate.y / length);
}

inline float BEVector2::Dot(const BEVector2& _rhs) const
{
	return coordinate.x * _rhs.coordinate.x + coordinate.y * _rhs.coordinate.y;
}

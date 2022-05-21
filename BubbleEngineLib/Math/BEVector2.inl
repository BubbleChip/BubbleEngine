#include <math.h>
#include "BEVector2.h"
#include "BEMatrix2.h"

inline BEVector2::BEVector2(float _x, float _y) 
	: x(_x), y(_y)
{
}

inline BEVector2 BEVector2::operator*(const float _rhs) const 
{
	return BEVector2(x * _rhs, y * _rhs);
}

inline BEVector2 BEVector2::operator+(const BEVector2& _rhs) const 
{
	return BEVector2(x + _rhs.x, y + _rhs.y);
}

inline BEVector2 BEVector2::operator-(const BEVector2& _rhs) const 
{
	return BEVector2(x - _rhs.x, y - _rhs.y);
}

inline bool BEVector2::operator==(const BEVector2& _rhs) const 
{
	return x == _rhs.x && y == _rhs.y;
}

inline bool BEVector2::operator!=(const BEVector2& _rhs) const 
{
	return x != _rhs.x && y != _rhs.y;
}

inline BEVector2 BEVector2::operator*(const BEMatrix2& _rhs) const 
{
	return { (x * _rhs.m00 + y * _rhs.m10)
			   , (x * _rhs.m01 + y * _rhs.m11) };
}

inline BEVector2 BEVector2::operator*=(const BEMatrix2& _rhs) 
{
	BEVector2 v(*this);
	x = v.x * _rhs.m00 + v.y * _rhs.m10;
	y = v.x * _rhs.m01 + v.y * _rhs.m11;
	return *this;
}

inline float BEVector2::GetLength() const 
{
	return sqrtf(
		x * x +
		y * y
	);
}

inline BEVector2 BEVector2::GetNormalized() const 
{
	float length = GetLength();

	return BEVector2(x / length, y / length);
}

inline float BEVector2::Dot(const BEVector2& _rhs) const 
{
	return x * _rhs.x + y * _rhs.y;
}

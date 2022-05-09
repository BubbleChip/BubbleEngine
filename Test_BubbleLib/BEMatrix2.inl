#include "BEMatrix2.h"

inline BEMatrix2::BEMatrix2(float _00, float _01, float _10, float _11)
{
	element.m00 = _00;
	element.m01 = _01;
	element.m10 = _10;
	element.m11 = _11;
}

inline BEMatrix2 BEMatrix2::operator*(const float _rhs) const
{
	BEMatrix2 result = BEMatrix2(this);

	for (int i = 0, iMax = 2; i < iMax; i++)
	{
		for (int j = 0, jMax = 2; j < jMax; j++)
		{
			result.arr[i][j] *= _rhs;
		}
	}

	return result;
}

inline BEMatrix2 BEMatrix2::operator+(const BEMatrix2& _rhs) const
{
	return BEMatrix2();
}

inline BEMatrix2 BEMatrix2::operator-(const BEMatrix2& _rhs) const
{
	return BEMatrix2();
}

inline BEMatrix2 BEMatrix2::operator*(const BEMatrix2& _rhs) const
{
	return BEMatrix2();
}

inline bool BEMatrix2::operator==(const BEMatrix2& _rhs) const
{
	return false;
}

inline bool BEMatrix2::operator!=(const BEMatrix2& _rhs) const
{
	return false;
}

inline BEMatrix2 BEMatrix2::GetTransposeMatrix() const
{
	return BEMatrix2();
}

inline BEMatrix2 BEMatrix2::GetInverseMatrix() const
{
	return BEMatrix2();
}

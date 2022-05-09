#include "BEMatrix2.h"
#include <math.h>

inline BEMatrix2::BEMatrix2(float _00, float _01, float _10, float _11)
{
	element.m00 = _00;
	element.m01 = _01;
	element.m10 = _10;
	element.m11 = _11;
}

inline BEMatrix2 BEMatrix2::operator*(const float _rhs) const
{
	BEMatrix2 result = BEMatrix2(*this);

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
	BEMatrix2 result = BEMatrix2(*this);

	for (int i = 0, iMax = 2; i < iMax; i++)
	{
		for (int j = 0, jMax = 2; j < jMax; j++)
		{
			result.arr[i][j] = arr[i][j] + _rhs.arr[i][j];
		}
	}

	return result;
}

inline BEMatrix2 BEMatrix2::operator-(const BEMatrix2& _rhs) const
{
	BEMatrix2 result = BEMatrix2(*this);

	for (int i = 0, iMax = 2; i < iMax; i++)
	{
		for (int j = 0, jMax = 2; j < jMax; j++)
		{
			result.arr[i][j] = arr[i][j] - _rhs.arr[i][j];
		}
	}

	return result;
}

inline BEMatrix2 BEMatrix2::operator*(const BEMatrix2& _rhs) const
{
	BEMatrix2 result = BEMatrix2(*this);

	for (int i = 0, iMax = 2; i < iMax; i++)
	{
		for (int j = 0, jMax = 2; j < jMax; j++)
		{
			result.arr[i][j] = 0;

			for (int k = 0,kMax = 2; k < kMax; k++)
			{
				result.arr[i][j] += arr[i][k] * _rhs.arr[j][k];
			}
		}
	}

	return result; 
}

inline bool BEMatrix2::operator==(const BEMatrix2& _rhs) const
{
	for (int i = 0, iMax = 2; i < iMax; i++)
	{
		for (int j = 0, jMax = 2; j < jMax; j++)
		{
			if (arr[i][j] != _rhs.arr[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

inline bool BEMatrix2::operator!=(const BEMatrix2& _rhs) const
{
	for (int i = 0, iMax = 2; i < iMax; i++)
	{
		for (int j = 0, jMax = 2; j < jMax; j++)
		{
			if (arr[i][j] == _rhs.arr[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

inline BEMatrix2 BEMatrix2::GetTransposeMatrix() const
{
	BEMatrix2 result = BEMatrix2(*this);

	for (int i = 0, iMax = 2; i < iMax; i++)
	{
		for (int j = 0, jMax = 2; j < jMax; j++)
		{
			result.arr[i][j] = arr[j][i];
		}
	}

	return result;
}

inline bool BEMatrix2::GetInverseMatrix(BEMatrix2& _outResult) const
{
	float determinant = 1 / (arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0]);

	if ( abs(determinant) < FLT_EPSILON)
	{
		_outResult = BEMatrix2(1.0f, 0.0f, 0.0f, 1.0f);
		return false;
	}

	_outResult = BEMatrix2(arr[1][1], -arr[0][1], -arr[1][0], arr[0][0]);
	_outResult = _outResult * determinant;

	return true;
}

inline std::string BEMatrix2::ToString() const
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

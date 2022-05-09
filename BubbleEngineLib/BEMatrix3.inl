#include "BEMatrix3.h"
#include <math.h>
#include <iostream>

inline BEMatrix3::BEMatrix3(float _00, float _01, float _02, float _10, float _11, float _12, float _20, float _21, float _22)
{
	element.m00 = _00;
	element.m01 = _01;
	element.m02 = _02;
	element.m10 = _10;
	element.m11 = _11;
	element.m12 = _12;
	element.m20 = _20;
	element.m21 = _21;
	element.m22 = _22;
}

inline BEMatrix3 BEMatrix3::operator*(const float _rhs) const
{
	BEMatrix3 result = BEMatrix3(*this);

	for (int i = 0, iMax = ROW_COL_COUNT; i < iMax; i++)
	{
		for (int j = 0, jMax = ROW_COL_COUNT; j < jMax; j++)
		{
			result.arr[i][j] *= _rhs;
		}
	}

	return result;
}

inline BEMatrix3 BEMatrix3::operator+(const BEMatrix3& _rhs) const
{
	BEMatrix3 result = BEMatrix3(*this);

	for (int i = 0, iMax = ROW_COL_COUNT; i < iMax; i++)
	{
		for (int j = 0, jMax = ROW_COL_COUNT; j < jMax; j++)
		{
			result.arr[i][j] = arr[i][j] + _rhs.arr[i][j];
		}
	}

	return result;
}

inline BEMatrix3 BEMatrix3::operator-(const BEMatrix3& _rhs) const
{
	BEMatrix3 result = BEMatrix3(*this);

	for (int i = 0, iMax = ROW_COL_COUNT; i < iMax; i++)
	{
		for (int j = 0, jMax = ROW_COL_COUNT; j < jMax; j++)
		{
			result.arr[i][j] = arr[i][j] - _rhs.arr[i][j];
		}
	}

	return result;
}

inline BEMatrix3 BEMatrix3::operator*(const BEMatrix3& _rhs) const
{
	BEMatrix3 result = BEMatrix3(*this);

	for (int i = 0, iMax = ROW_COL_COUNT; i < iMax; i++)
	{
		for (int j = 0, jMax = ROW_COL_COUNT; j < jMax; j++)
		{
			result.arr[i][j] = 0;

			for (int k = 0, kMax = ROW_COL_COUNT; k < kMax; k++)
			{
				result.arr[i][j] += arr[i][k] * _rhs.arr[j][k];
			}
		}
	}

	return result;
}

inline bool BEMatrix3::operator==(const BEMatrix3& _rhs) const
{
	for (int i = 0, iMax = ROW_COL_COUNT; i < iMax; i++)
	{
		for (int j = 0, jMax = ROW_COL_COUNT; j < jMax; j++)
		{
			if (arr[i][j] != _rhs.arr[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

inline bool BEMatrix3::operator!=(const BEMatrix3& _rhs) const
{
	for (int i = 0, iMax = ROW_COL_COUNT; i < iMax; i++)
	{
		for (int j = 0, jMax = ROW_COL_COUNT; j < jMax; j++)
		{
			if (arr[i][j] == _rhs.arr[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

inline BEMatrix3 BEMatrix3::GetTransposeMatrix() const
{
	BEMatrix3 result = BEMatrix3(*this);

	for (int i = 0, iMax = ROW_COL_COUNT; i < iMax; i++)
	{
		for (int j = 0, jMax = ROW_COL_COUNT; j < jMax; j++)
		{
			result.arr[i][j] = arr[j][i];
		}
	}

	return result;
}

inline float BEMatrix3::GetCofactor(const float _minorMatrixArray[], const int _rowColCount, const int _targetRow, const int _targetCol) const
{
	if (_rowColCount == 1)
	{
		int negative = (_targetCol + _targetRow) % 2 != 0 ? -1 : 1;

		std::cout << _minorMatrixArray[0] * negative << std::endl;
		return _minorMatrixArray[0] * negative;
	}

	int minorSize = _rowColCount - 1;
	float* minorMatrix = new float[minorSize * minorSize];

	int targetRow = 0;
	for (int i = 0; i < _rowColCount; i++)
	{
		if (i == _targetRow)
		{
			continue;
		}

		int targetCol = 0;
		for (int j = 0; j < _rowColCount; j++)
		{
			if (j == _targetCol)
			{
				continue;
			}

			minorMatrix[targetRow * minorSize + targetCol] = _minorMatrixArray[i * _rowColCount + j];
			targetCol++;
		}

		targetRow++;
	}

	float minorCofactor = 0.0f;
	for (int i = 0; i < minorSize; i++)
	{
		for (int j = 0; j < minorSize; j++)
		{
			minorCofactor += GetCofactor(minorMatrix, minorSize, _targetRow, _targetCol);
		}
	}
		
	delete[] minorMatrix;

	return minorCofactor;
}

inline float BEMatrix3::GetMatrixDeterminant() const
{
//
//
//	float result = 0.0f;
//	int minorMatrixRowColCount = _rowColCount - 1;
//
//	for (int k = 0, kMax = _rowColCount; k < kMax; k++)
//	{
//		float* minorMatrix = new float[minorMatrixRowColCount];
//
//		int targetRow = 0;
//		for (int i = 1; i < _rowColCount; i++)
//		{
//			if (k == j)
//			{
//				continue;
//			}
//
//			int targetCol = 0;
//			for (int j = 0; j < _rowColCount; j++)
//			{
//				if (k == j)
//				{
//					continue;
//				}
//
//				minorMatrix[targetRow * minorMatrixRowColCount + targetCol] = _matrixArray[i * _rowColCount + j];
//				targetCol++;
//			}
//
//			targetRow++;
//		}
//
//		result += _matrixArray[k] * roundf(powf(-1, 1 + k)) * GetMatrixDeterminant(minorMatrix, minorMatrixRowColCount);
//
//		//delete[] minorMatrix;
//	}
//
//
//	return result;

	return GetCofactor(arr2, ROW_COL_COUNT, 0, 0);
}

inline bool BEMatrix3::GetInverseMatrix(BEMatrix3& _outResult) const
{
	/*float determinant = GetMatrixDeterminant(arr2, ROW_COL_COUNT);

	if (abs(determinant) < FLT_EPSILON)
	{
		_outResult = BEMatrix3(
			1, 0, 0,
			0, 1, 0,
			0, 0, 1
		);
		return false;
	}

	_outResult = BEMatrix3(*this);
	_outResult = _outResult * determinant;


	return true;*/
}

inline std::string BEMatrix3::ToString() const
{
	std::string result = " :: Matrix ::\n";

	for (int i = 0, iMax = ROW_COL_COUNT; i < iMax; i++)
	{
		for (int j = 0, jMax = ROW_COL_COUNT; j < jMax; j++)
		{
			result += std::to_string(arr[i][j]) + "\t";
		}
		result += "\n";
	}

	return result;
}

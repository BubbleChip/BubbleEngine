#pragma once

#include <string>

class BEMatrix3
{
public:
	inline BEMatrix3() = default;
	inline ~BEMatrix3() = default;
	inline BEMatrix3(float _00, float _01, float _02, float _10, float _11, float _12, float _20, float _21, float _22);

	inline BEMatrix3 operator * (const float _rhs) const;

	inline BEMatrix3 operator + (const BEMatrix3& _rhs) const;
	inline BEMatrix3 operator - (const BEMatrix3& _rhs) const;
	inline BEMatrix3 operator * (const BEMatrix3& _rhs) const;

	inline bool operator == (const BEMatrix3& _rhs) const;
	inline bool operator != (const BEMatrix3& _rhs) const;

	inline BEMatrix3 GetTransposeMatrix() const;

	inline float GetCofactor(const float _minorMatrixArray[], const int _rowColCount, const int _targetRow, const int _targetCol) const;
	inline float GetMatrixDeterminant() const;
	inline bool GetInverseMatrix(BEMatrix3& _outResult) const;

	inline std::string ToString() const;

private:
	static const int ROW_COL_COUNT = 3;

	union
	{
		struct
		{
			float m00;
			float m01;
			float m02;
			float m10;
			float m11;
			float m12; 
			float m20;
			float m21;
			float m22;
		} element;

		float arr[ROW_COL_COUNT][ROW_COL_COUNT];
		float arr2[ROW_COL_COUNT * ROW_COL_COUNT];
	};

};

#include "BEMatrix3.inl"
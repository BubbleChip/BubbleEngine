#pragma once

#include <string>

class BEMatrix2
{
public:
	constexpr  BEMatrix2();
	constexpr  BEMatrix2(float _00, float _01, float _10, float _11);

	constexpr  BEMatrix2 operator * (const float _rhs) const;

	constexpr BEMatrix2 operator + (const BEMatrix2& _rhs) const;
	constexpr BEMatrix2 operator - (const BEMatrix2& _rhs) const;
	constexpr BEMatrix2 operator * (const BEMatrix2& _rhs) const;

	constexpr BEMatrix2& operator+=(const BEMatrix2& _rhs) noexcept;
	constexpr BEMatrix2& operator-=(const BEMatrix2& _rhs) noexcept;
	constexpr BEMatrix2& operator*=(const BEMatrix2& _rhs) noexcept;
	constexpr BEMatrix2& operator*=(const float _rhs) noexcept;

	constexpr  bool operator == (const BEMatrix2& _rhs) const;
	constexpr  bool operator != (const BEMatrix2& _rhs) const;

	constexpr  BEMatrix2 GetTransposeMatrix() const;
	constexpr  bool GetInverseMatrix(BEMatrix2& _outResult) const;
	constexpr float GetMatrixDeterminant() const noexcept;

	constexpr  std::string ToString() const;

private:
	static const int ROW_COL_COUNT = 2;

	union
	{
		struct
		{
			float m00;
			float m01;
			float m10;
			float m11;
		};

		float arr[ROW_COL_COUNT][ROW_COL_COUNT];
	};

};

#include "BEMatrix2.inl"
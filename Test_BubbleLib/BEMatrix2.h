#pragma once

class BEMatrix2
{
public:
	inline BEMatrix2() = default;
	inline ~BEMatrix2() = default;
	inline BEMatrix2(float _00, float _01, float _10, float _11);

	inline BEMatrix2 operator * (const float _rhs) const;

	inline BEMatrix2 operator + (const BEMatrix2& _rhs) const;
	inline BEMatrix2 operator - (const BEMatrix2& _rhs) const;
	inline BEMatrix2 operator * (const BEMatrix2& _rhs) const;

	inline bool operator == (const BEMatrix2& _rhs) const;
	inline bool operator != (const BEMatrix2& _rhs) const;

	inline BEMatrix2 GetTransposeMatrix() const;
	inline BEMatrix2 GetInverseMatrix() const;

private:
	union
	{
		struct
		{
			float m00;
			float m01;
			float m10;
			float m11;
		} element;

		float arr[2][2];
	};
};

#include "BEMatrix2.inl"
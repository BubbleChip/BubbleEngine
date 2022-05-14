#pragma once

#include <string>

class BEMatrix3
{
public:
	constexpr BEMatrix3();
	constexpr BEMatrix3(float _00, float _01, float _02, float _10, float _11, float _12, float _20, float _21, float _22);


	constexpr BEMatrix3 operator * (const float _rhs) const;
	constexpr BEMatrix3 operator * (const BEMatrix3& _rhs) const;
	constexpr BEMatrix3 operator + (const BEMatrix3& _rhs) const;
	constexpr BEMatrix3 operator - (const BEMatrix3& _rhs) const;

	constexpr BEMatrix3& operator*=(const float _rhs) noexcept;
	constexpr BEMatrix3& operator*=(const BEMatrix3& _rhs) noexcept;
	constexpr BEMatrix3& operator+=(const BEMatrix3& _rhs) noexcept;
	constexpr BEMatrix3& operator-=(const BEMatrix3& _rhs) noexcept;

	constexpr bool operator == (const BEMatrix3& _rhs) const;
	constexpr bool operator != (const BEMatrix3& _rhs) const;

	constexpr BEMatrix3 GetTransposeMatrix() const;

	constexpr float GetMatrixDeterminant() const;
	constexpr bool GetInverseMatrix(BEMatrix3& _outResult) const;

	constexpr std::string ToString() const;

private:
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
		};

		float arr[3][3];
	};

};

#include "BEMatrix3.inl"
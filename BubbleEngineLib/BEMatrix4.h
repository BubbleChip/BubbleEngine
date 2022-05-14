#pragma once

#include <string>

class BEMatrix4
{
public:
	constexpr BEMatrix4();
	constexpr BEMatrix4(float _00, float _01, float _02, float _03, float _10, float _11, float _12, float _13, float _20, float _21, float _22, float _23, float _30, float _31, float _32, float _33);


	constexpr BEMatrix4 operator * (const float _rhs) const;
	constexpr BEMatrix4 operator * (const BEMatrix4& _rhs) const;
	constexpr BEMatrix4 operator + (const BEMatrix4& _rhs) const;
	constexpr BEMatrix4 operator - (const BEMatrix4& _rhs) const;

	constexpr BEMatrix4& operator*=(const float _rhs) noexcept;
	constexpr BEMatrix4& operator*=(const BEMatrix4& _rhs) noexcept;
	constexpr BEMatrix4& operator+=(const BEMatrix4& _rhs) noexcept;
	constexpr BEMatrix4& operator-=(const BEMatrix4& _rhs) noexcept;

	constexpr bool operator == (const BEMatrix4& _rhs) const;
	constexpr bool operator != (const BEMatrix4& _rhs) const;

	constexpr BEMatrix4 GetTransposeMatrix() const;

	constexpr float GetMatrixDeterminant() const;
	constexpr bool GetInverseMatrix(BEMatrix4& _outResult) const;

	constexpr std::string ToString() const;

private:
	union
	{
		struct
		{
			float m00;
			float m01;
			float m02;
			float m03;
			float m10;
			float m11;
			float m12;
			float m13;
			float m20;
			float m21;
			float m22;
			float m23;
			float m30;
			float m31;
			float m32;
			float m33;
		};

		float arr[4][4];
	};

};

#include "BEMatrix4.inl"
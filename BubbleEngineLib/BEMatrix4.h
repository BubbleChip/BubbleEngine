#pragma once

#include <string>

class BEMatrix4
{
public:
	inline BEMatrix4() ;
	inline BEMatrix4(float _00, float _01, float _02, float _03, float _10, float _11, float _12, float _13, float _20, float _21, float _22, float _23, float _30, float _31, float _32, float _33) ;


	inline BEMatrix4 operator * (const float _rhs) const ;
	inline BEMatrix4 operator * (const BEMatrix4& _rhs) const ;
	inline BEMatrix4 operator + (const BEMatrix4& _rhs) const ;
	inline BEMatrix4 operator - (const BEMatrix4& _rhs) const ;

	inline BEMatrix4& operator*=(const float _rhs) ;
	inline BEMatrix4& operator*=(const BEMatrix4& _rhs) ;
	inline BEMatrix4& operator+=(const BEMatrix4& _rhs) ;
	inline BEMatrix4& operator-=(const BEMatrix4& _rhs) ;

	inline bool operator == (const BEMatrix4& _rhs) const ;
	inline bool operator != (const BEMatrix4& _rhs) const ;

	inline BEMatrix4 GetTransposeMatrix() const ;

	inline float GetMatrixDeterminant() const ;
	inline bool GetInverseMatrix(BEMatrix4& _outResult) const ;

	inline std::string ToString() const;

public:
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
#pragma once

class BEMatrix3;

class BEVector3
{
public:
	inline BEVector3() = default;
	inline ~BEVector3() = default;
	inline BEVector3(float _x, float _y, float _z) ;

	inline BEVector3 operator * (const float _rhs) const ;

	inline BEVector3 operator + (const BEVector3& _rhs) const ;
	inline BEVector3 operator - (const BEVector3& _rhs) const ;
	inline bool operator == (const BEVector3& _rhs) const ;
	inline bool operator != (const BEVector3& _rhs) const ;

	inline BEVector3 operator * (const BEMatrix3& _rhs) const ;
	inline BEVector3 operator *=(const BEMatrix3& _rhs) ;

	inline float GetLength() const ;
	inline BEVector3 GetNormalized() const ;

	inline float Dot(const BEVector3& _rhs) const ;
	inline BEVector3 Cross(const BEVector3& _rhs) const ;


public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};

		float arr[3];
	};
};

#include "BEVector3.inl"
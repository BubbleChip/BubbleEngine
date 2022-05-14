#pragma once

class BEMatrix2;

class BEVector2
{
public:
	inline BEVector2() = default;
	inline ~BEVector2() = default;
	inline BEVector2(float _x, float _y) ;

	inline BEVector2 operator * (const float _rhs) const ;

	inline BEVector2 operator + (const BEVector2& _rhs) const ;
	inline BEVector2 operator - (const BEVector2& _rhs) const ;
	inline bool operator == (const BEVector2& _rhs) const ;
	inline bool operator != (const BEVector2& _rhs) const ;
	
	inline BEVector2 operator * (const BEMatrix2& _rhs) const ;
	inline BEVector2 operator *= (const BEMatrix2& _rhs);

	inline float GetLength() const ;
	inline BEVector2 GetNormalized() const ;

	inline float Dot(const BEVector2& _rhs) const ;


public:
	union
	{
		struct
		{
			float x;
			float y;
		};

		float arr[2];
	};
};

#include "BEVector2.inl"
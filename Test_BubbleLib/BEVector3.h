#pragma once

class BEVector3
{
public:
	inline BEVector3() = default;
	inline ~BEVector3() = default;
	inline BEVector3(float _x, float _y, float _z);

	inline BEVector3 operator * (const float _rhs) const;

	inline BEVector3 operator + (const BEVector3& _rhs) const;
	inline BEVector3 operator - (const BEVector3& _rhs) const;
	inline bool operator == (const BEVector3& _rhs) const;
	inline bool operator != (const BEVector3& _rhs) const;

	//TODO
	//inline BEVector3 operator * (BEMatrix3 _rhs) const;

	inline float GetLength() const;
	inline BEVector3 GetNormalized() const;

	inline float Dot(const BEVector3& _rhs) const;
	inline BEVector3 Cross(const BEVector3& _rhs) const;


private:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		} coordinate;

		float arr[3];
	};
};

#include "BEVector3.inl"
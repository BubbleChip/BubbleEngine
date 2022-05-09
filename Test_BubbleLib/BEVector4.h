#pragma once

class BEVector4
{
public:
	inline BEVector4() = default;
	inline ~BEVector4() = default;
	inline BEVector4(float _x, float _y, float _z, float _w);

	inline BEVector4 operator * (const float _rhs) const;

	inline BEVector4 operator + (const BEVector4& _rhs) const;
	inline BEVector4 operator - (const BEVector4& _rhs) const;
	inline bool operator == (const BEVector4& _rhs) const;
	inline bool operator != (const BEVector4& _rhs) const;

	//TODO
	//inline BEVector4 operator * (BEMatrix4 _rhs) const;

	inline float GetLength() const;
	inline BEVector4 GetNormalized() const;

	inline float Dot(const BEVector4& _rhs) const;

private:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		} coordinate;

		float arr[4];
	};
};

#include "BEVector4.inl"
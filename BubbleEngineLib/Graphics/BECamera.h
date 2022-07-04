#pragma once
#include "BECore/BEInclude.h"
#include "Math/BEVector3.h"
#include "Math/BEMatrix4.h"

class BEL_API BECamera final
{
public:
	BECamera();
	~BECamera() = default;

	void SetupViewMatrix(const BEVector3& pos, const BEVector3& targetPos, const BEVector3& worldUp);

	/// use reversed-Z, it requires clearing Z to 0.0f and using a GREATER variant depth test.
	void SetPerspective(float vFov, float aspect, float nearZ, float farZ);
	void SetOrthographics(float width, float height, float nearZ, float farZ);
	bool IsPerspective() const;
	bool IsOrthographic() const;

	float NearZ() const { return nearZ; }
	float FarZ() const { return farZ; }
	BEVector3 Position() const;
	BEMatrix4 ViewMatrix() const;
	BEMatrix4 ProjectionMatrix() const;

private:
	float nearZ;
	float farZ;
	BEMatrix4 viewMatrix;
	BEMatrix4 projectionMatrix;
};

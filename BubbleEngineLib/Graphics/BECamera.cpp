#include "BECamera.h"
#include "Math/BEVector3.h"

BECamera::BECamera()
    : nearZ(0.f)
    , farZ(0.f)
{
}

void BECamera::SetupViewMatrix(const BEVector3& pos, const BEVector3& targetPos, const BEVector3& worldUp)
{
    BEVector3 forward = (targetPos - pos).Normalize();
    BEVector3 right = worldUp.Cross(forward).Normalize();
    BEVector3 up = forward.Cross(right);

    float x = -pos.Dot(right);
    float y = -pos.Dot(up);
    float z = -pos.Dot(forward);

    this->viewMatrix = {
        right.x, up.x, forward.x, 0.0f,
        right.y, up.y, forward.y, 0.0f,
        right.z, up.z, forward.z, 0.0f,
        x, y, z, 1.0f
    };
}

void BECamera::SetPerspective(float vFov, float aspect, float nearZ, float farZ)
{
    BEASSERT_DEBUG(vFov > 0);
    BEASSERT_DEBUG(aspect > 0);
    BEASSERT_DEBUG(nearZ > 0);
    BEASSERT_DEBUG(farZ > 0);
    BEASSERT_DEBUG(nearZ < farZ);

    this->nearZ = nearZ;
    this->farZ = farZ;

    // reversed-Z projection matrix
    // it requires clearing Z to 0.0f and using a GREATER variant depth test.
    // ref. https://developer.nvidia.com/content/depth-precision-visualized#:~:text=Reversed-Z%20erases%20the%20distinctions,without%20affecting%20precision%20at%20all.
    float f = 1.0f / tanf(vFov / 2.0f);
    float scale = nearZ / (nearZ - farZ);
    float bias = -farZ * scale;
    this->projectionMatrix = {
        f / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, f, 0.0f, 0.0f,
        0.0f, 0.0f, scale, 1.0f,
        0.0f, 0.0f, bias, 0.0f
    };
}

void BECamera::SetOrthographics(float width, float height, float nearZ, float farZ)
{
    BEASSERT_DEBUG(width > 0);
    BEASSERT_DEBUG(height > 0);
    BEASSERT_DEBUG(nearZ > farZ);

    this->nearZ = nearZ;
    this->farZ = farZ;

    float range = 1.0f / (farZ - nearZ);
    this->projectionMatrix = {
        2.0f / width, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / height, 0.0f, 0.0f,
        0.0f, 0.0f, range, 1.0f,
        0.0f, 0.0f, -range * nearZ, 1.0f
    };
}

bool BECamera::IsPerspective() const
{
    return projectionMatrix.m33 == 0.0f;
}

bool BECamera::IsOrthographic() const
{
    return projectionMatrix.m33 == 1.0f;
}

BEVector3 BECamera::Position() const
{
    return { viewMatrix.arr[0][0], viewMatrix.arr[0][1], viewMatrix.arr[0][2] };
}

BEMatrix4 BECamera::ViewMatrix() const
{
    return viewMatrix;
}

BEMatrix4 BECamera::ProjectionMatrix() const
{
    return projectionMatrix;
}
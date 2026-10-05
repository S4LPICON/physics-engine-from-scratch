#include "camera/camera.h"

Camera::Camera()
{
    position.x = 0.0f;
    position.y = 0.0f;
    position.z = 0.0f;

    rotation.x = 0.0f;
    rotation.y = 0.0f;
    rotation.z = 0.0f;

    fov = 70.0f;
    aspectRatio = 800.0f / 600.0f;
    nearPlane = 0.1f;
    farPlane = 1000.0f;
}

Mat4 Camera::getViewMatrix() const
{
    Vec3 inversePosition;

    inversePosition.x = -position.x;
    inversePosition.y = -position.y;
    inversePosition.z = -position.z;

    Mat4 translation =
        Mat4::translation(inversePosition);

    Mat4 rotationX =
        Mat4::rotationX(-rotation.x);

    Mat4 rotationY =
        Mat4::rotationY(-rotation.y);

    Mat4 rotationZ =
        Mat4::rotationZ(-rotation.z);

    return rotationX * rotationY * rotationZ * translation;
}

Mat4 Camera::getProjectionMatrix() const
{
    Mat4 result{};

    float fovRadians = fov * 3.14159265359f / 180.0f;

    float f = 1.0f / std::tan(fovRadians / 2.0f);

    result.m[0][0] = f / aspectRatio;
    result.m[1][1] = f;

    result.m[2][2] =
        (farPlane + nearPlane) /
        (nearPlane - farPlane);

    result.m[2][3] =
        (2.0f * farPlane * nearPlane) /
        (nearPlane - farPlane);

    result.m[3][2] = -1.0f;

    return result;
}
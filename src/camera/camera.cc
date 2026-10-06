#include "camera/camera.h"

#include <cmath>

namespace {

constexpr float PI = 3.14159265358979323846f;

/**
 * @brief Convierte grados sexagesimales a radianes.
 */
[[nodiscard]] constexpr float degreesToRadians(float degrees) noexcept {
    return degrees * (PI / 180.0f);
}

}

Camera::Camera()
    : position{0.0f, 0.0f, 0.0f}
    , rotation{0.0f, 0.0f, 0.0f}
    , fov{70.0f}
    , aspectRatio{640.0f / 448.0f}
    , nearPlane{0.1f}
    , farPlane{1000.0f}
{
}

Mat4 Camera::getViewMatrix() const
{
    const Vec3 invPos{ -position.x, -position.y, -position.z };

    const Mat4 invTranslation = Mat4::translation(invPos);
    const Mat4 invRotationX   = Mat4::rotationX(-rotation.x);
    const Mat4 invRotationY   = Mat4::rotationY(-rotation.y);
    const Mat4 invRotationZ   = Mat4::rotationZ(-rotation.z);

    return invRotationZ * invRotationX * invRotationY * invTranslation;
}

Mat4 Camera::getProjectionMatrix() const
{
    Mat4 result{};

    const float fovRadians = degreesToRadians(fov);
    const float f = 1.0f / std::tan(fovRadians * 0.5f);
    const float depthRange = nearPlane - farPlane;

    // escala X e Y en base al FOV y la relacion de aspecto (la pntalla)
    result.m[0][0] = f / aspectRatio;
    result.m[1][1] = f;

    // mapeo Z a NDC en el rango [-1, 1] (estandar OpenGL)
    result.m[2][2] = (farPlane + nearPlane) / depthRange;
    result.m[2][3] = (2.0f * farPlane * nearPlane) / depthRange;

    // guarda la profundidad Z lineal en W_clip para la division por perspectiva
    result.m[3][2] = -1.0f;
    result.m[3][3] = 0.0f;

    return result;
}
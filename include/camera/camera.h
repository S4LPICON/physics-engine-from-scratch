#pragma once

#include "math/vec3.h"
#include "math/mat4.h"

class Camera
{
public:
    Camera();

    Vec3 position;
    Vec3 rotation;

    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    Mat4 getViewMatrix() const;
    Mat4 getProjectionMatrix() const;
};
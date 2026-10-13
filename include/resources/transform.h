#pragma once

#include "math/vec3.h"
#include "math/mat4.h"

class Transform {
public:
    Vec3 position{0.0f, 0.0f, 0.0f};

    Vec3 rotation{0.0f, 0.0f, 0.0f};

    Vec3 scale{1.0f, 1.0f, 1.0f};

    Mat4 getMatrix() const {
        Mat4 translation =
            Mat4::translation(position);

        Mat4 rotationX =
            Mat4::rotationX(rotation.x);

        Mat4 rotationY =
            Mat4::rotationY(rotation.y);

        Mat4 rotationZ =
            Mat4::rotationZ(rotation.z);

        Mat4 scaling =
            Mat4::scale(scale);

        return translation *
               rotationY *
               rotationX *
               rotationZ *
               scaling;
    }
};
#pragma once

#include "vec3.h"

struct Vec4 {
    float x;
    float y;
    float z;
    float w;

    Vec4(float x, float y, float z, float w)
        : x(x), y(y), z(z), w(w) {}

    Vec4(const Vec3& v, float w)
        : x(v.x), y(v.y), z(v.z), w(w) {}
};
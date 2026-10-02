#pragma once

#include <cmath>
#include "vec3.h"
#include "vec4.h"

class Mat4 {
public:
    float m[4][4]{};

    static Mat4 identity() {
        Mat4 result;

        for (int i = 0; i < 4; i++)
            result.m[i][i] = 1.0f;

        return result;
    }

    static Mat4 translation(const Vec3& position) {
        Mat4 result = identity();

        result.m[0][3] = position.x;
        result.m[1][3] = position.y;
        result.m[2][3] = position.z;

        return result;
    }

    static Mat4 scale(const Vec3& scale) {
        Mat4 result = identity();

        result.m[0][0] = scale.x;
        result.m[1][1] = scale.y;
        result.m[2][2] = scale.z;

        return result;
    }

    static Mat4 rotationX(float angle) {
        Mat4 result = identity();

        float c = std::cos(angle);
        float s = std::sin(angle);

        result.m[1][1] = c;
        result.m[1][2] = -s;
        result.m[2][1] = s;
        result.m[2][2] = c;

        return result;
    }

    static Mat4 rotationY(float angle) {
        Mat4 result = identity();

        float c = std::cos(angle);
        float s = std::sin(angle);

        result.m[0][0] = c;
        result.m[0][2] = s;
        result.m[2][0] = -s;
        result.m[2][2] = c;

        return result;
    }

    static Mat4 rotationZ(float angle) {
        Mat4 result = identity();

        float c = std::cos(angle);
        float s = std::sin(angle);

        result.m[0][0] = c;
        result.m[0][1] = -s;
        result.m[1][0] = s;
        result.m[1][1] = c;

        return result;
    }

    Mat4 operator*(const Mat4& other) const {
        Mat4 result;

        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                for (int k = 0; k < 4; k++) {
                    result.m[row][col] +=
                        m[row][k] * other.m[k][col];
                }
            }
        }

        return result;
    }

    Vec4 operator*(const Vec4& v) const {
        return {
            m[0][0] * v.x + m[0][1] * v.y +
            m[0][2] * v.z + m[0][3] * v.w,

            m[1][0] * v.x + m[1][1] * v.y +
            m[1][2] * v.z + m[1][3] * v.w,

            m[2][0] * v.x + m[2][1] * v.y +
            m[2][2] * v.z + m[2][3] * v.w,

            m[3][0] * v.x + m[3][1] * v.y +
            m[3][2] * v.z + m[3][3] * v.w
        };
    }
};
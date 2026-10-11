#pragma once

#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <cstdint>
#include "geometry/geometry.h"

struct Point3D {
    int x{0}, y{0};
    float z{0.0f};
    float u{0.0f};
    float v{0.0f};
    float invW{1.0f};
};

struct Triangle {
    Point3D a, b, c;
};

void drawTriangle(const Triangle& t, uint32_t color);
inline uint32_t sampleTexture(const Texture& texture, float u, float v);
void drawTexturedTriangle(
    const Point3D& a, 
    const Point3D& b, 
    const Point3D& c, 
    const Texture& texture);

void drawLine(Point3D start, Point3D end, uint32_t color);
void drawLineDepth(Point3D start, Point3D end, uint32_t color);

#endif
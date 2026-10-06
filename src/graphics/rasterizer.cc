#include "graphics/rasterizer.h"
#include "graphics/framebuffer.h"
#include "geometry/mesh.h"

#include <iostream>
#include <algorithm>
#include <cmath>

namespace {

/**
 * @brief Evalúa la función de arista (2D Cross Product) entre dos puntos.
 */
inline float edgeFunction(const Point3D& a, const Point3D& b, float x, float y) {
    return (x - static_cast<float>(a.x)) * static_cast<float>(b.y - a.y) - 
           (y - static_cast<float>(a.y)) * static_cast<float>(b.x - a.x);
}

}

void drawTriangle(const Triangle& t, uint32_t color)
{
    int minX = std::min(t.a.x, std::min(t.b.x, t.c.x));
    int maxX = std::max(t.a.x, std::max(t.b.x, t.c.x));
    int minY = std::min(t.a.y, std::min(t.b.y, t.c.y));
    int maxY = std::max(t.a.y, std::max(t.b.y, t.c.y));

    minX = std::max(0, minX);
    maxX = std::min(WIDTH - 1, maxX);
    minY = std::max(0, minY);
    maxY = std::min(HEIGHT - 1, maxY);

    if (minX > maxX || minY > maxY) {
        return;
    }

    const float area = edgeFunction(t.a, t.b, static_cast<float>(t.c.x), static_cast<float>(t.c.y));
    if (std::abs(area) < 0.0001f) {
        return;
    }

    const float invArea = 1.0f / area;

    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            const float px = x + 0.5f;
            const float py = y + 0.5f;

            const float w0 = edgeFunction(t.b, t.c, px, py);
            const float w1 = edgeFunction(t.c, t.a, px, py);
            const float w2 = edgeFunction(t.a, t.b, px, py);

            const bool isInside = (area > 0.0f) 
                ? (w0 >= 0.0f && w1 >= 0.0f && w2 >= 0.0f)
                : (w0 <= 0.0f && w1 <= 0.0f && w2 <= 0.0f);

            if (isInside)
            {
                const float alpha = w0 * invArea;
                const float beta  = w1 * invArea;
                const float gamma = w2 * invArea;

                const float depth = alpha * t.a.z + beta * t.b.z + gamma * t.c.z;
                const int index = y * WIDTH + x;

                if (depth < zbuffer[index])
                {
                    zbuffer[index] = depth;
                    framebuffer[index] = color;
                }
            }
        }
    }
}


void drawTexturedTriangle(
    const Point3D& a, 
    const Point3D& b, 
    const Point3D& c, 
    const Texture& texture)
{

    int minX = std::max(0, std::min({a.x, b.x, c.x}));
    int maxX = std::min(WIDTH - 1, std::max({a.x, b.x, c.x}));
    int minY = std::max(0, std::min({a.y, b.y, c.y}));
    int maxY = std::min(HEIGHT - 1, std::max({a.y, b.y, c.y}));

    if (minX > maxX || minY > maxY) {
        return;
    }

    const float area = edgeFunction(a, b, static_cast<float>(c.x), static_cast<float>(c.y));
    if (std::abs(area) < 0.0001f) {
        return;
    }

    const float invArea = 1.0f / area;

    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            const float px = x + 0.5f;
            const float py = y + 0.5f;

            const float w0 = edgeFunction(b, c, px, py);
            const float w1 = edgeFunction(c, a, px, py);
            const float w2 = edgeFunction(a, b, px, py);

            const bool isInside = (area > 0.0f) 
                ? (w0 >= 0.0f && w1 >= 0.0f && w2 >= 0.0f)
                : (w0 <= 0.0f && w1 <= 0.0f && w2 <= 0.0f);

            if (isInside)
            {

                const float alpha = w0 * invArea;
                const float beta  = w1 * invArea;
                const float gamma = w2 * invArea;


                const float depth = alpha * a.z + beta * b.z + gamma * c.z;
                const int index = y * WIDTH + x;

                if (depth < zbuffer[index])
                {

                    const float interpolatedInvW = alpha * a.invW + beta * b.invW + gamma * c.invW;

                    const float interpolatedUoverW = alpha * a.u + beta * b.u + gamma * c.u;
                    const float interpolatedVoverW = alpha * a.v + beta * b.v + gamma * c.v;

                    const float realW = 1.0f / interpolatedInvW;

                    const float u = interpolatedUoverW * realW;
                    const float v = interpolatedVoverW * realW;

                    const uint32_t texColor = texture.sample(u, v);

                    zbuffer[index] = depth;
                    framebuffer[index] = texColor;
                }
            }
        }
    }
}


void drawLine(Point3D start, Point3D end, uint32_t color)
{
    int x = start.x;
    int y = start.y;

    const int dx = std::abs(end.x - start.x);
    const int dy = std::abs(end.y - start.y);
    const int sx = (start.x < end.x) ? 1 : -1;
    const int sy = (start.y < end.y) ? 1 : -1;

    int error = dx - dy;

    while (true)
    {
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            drawPixel(x, y, color);
        }

        if (x == end.x && y == end.y) break;

        const int error2 = 2 * error;
        if (error2 > -dy) { error -= dy; x += sx; }
        if (error2 < dx)  { error += dx; y += sy; }
    }
}

void drawLineDepth(Point3D start, Point3D end, uint32_t color)
{
    int x = start.x;
    int y = start.y;

    const int dx = std::abs(end.x - start.x);
    const int dy = std::abs(end.y - start.y);
    const int sx = (start.x < end.x) ? 1 : -1;
    const int sy = (start.y < end.y) ? 1 : -1;

    int error = dx - dy;

    const float stepCount = static_cast<float>(std::max(dx, dy));
    int currentStep = 0;

    while (true)
    {
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        {
            const float t = (stepCount > 0.0f) ? (static_cast<float>(currentStep) / stepCount) : 0.0f;
            const float depth = start.z + t * (end.z - start.z);

            const int index = y * WIDTH + x;

            if (depth <= zbuffer[index] + 0.001f)
            {
                framebuffer[index] = color;
            }
        }

        if (x == end.x && y == end.y) break;

        const int error2 = 2 * error;
        if (error2 > -dy) { error -= dy; x += sx; }
        if (error2 < dx)  { error += dx; y += sy; }

        currentStep++;
    }
}
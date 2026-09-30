
#include <iostream>
#include <algorithm>
#include <cmath>

#include "framebuffer.h"
#include "rasterizer.h"



static float edgeFunction(
    const Point& a,
    const Point& b,
    float x,
    float y)
{
    return (x - a.x) * (b.y - a.y)
         - (y - a.y) * (b.x - a.x);
}


void drawTriangle(const Triangle& t, uint32_t color)
{
    int minX = std::min({t.a.x, t.b.x, t.c.x});
    int maxX = std::max({t.a.x, t.b.x, t.c.x});

    int minY = std::min({t.a.y, t.b.y, t.c.y});
    int maxY = std::max({t.a.y, t.b.y, t.c.y});

    // No recorrer fuera del framebuffer
    minX = std::max(minX, 0);
    maxX = std::min(maxX, WIDTH - 1);

    minY = std::max(minY, 0);
    maxY = std::min(maxY, HEIGHT - 1);

    

    float area = edgeFunction(
        t.a,
        t.b,
        t.c.x,
        t.c.y
    );

    if (area == 0.0f)
        return;

    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            float px = x + 0.5f;
            float py = y + 0.5f;

            float w0 = edgeFunction(t.b, t.c, px, py);
            float w1 = edgeFunction(t.c, t.a, px, py);
            float w2 = edgeFunction(t.a, t.b, px, py);

            if ((w0 >= 0 && w1 >= 0 && w2 >= 0) ||
                (w0 <= 0 && w1 <= 0 && w2 <= 0))
            {
                float alpha = w0 / area;
                float beta  = w1 / area;
                float gamma = w2 / area;

                float depth =
                    alpha * t.a.z +
                    beta  * t.b.z +
                    gamma * t.c.z;

                int index = y * WIDTH + x;

                if (depth < zbuffer[index])
                {
                    zbuffer[index] = depth;
                    framebuffer[index] = color;
                }
            }
        }
    }}

void drawLine(Point start, Point end, uint32_t color)
{
    int x = start.x;
    int y = start.y;

    int dx = std::abs(end.x - start.x);
    int dy = std::abs(end.y - start.y);

    int sx = (start.x < end.x) ? 1 : -1;
    int sy = (start.y < end.y) ? 1 : -1;

    int error = dx - dy;

    while (true)
    {
        drawPixel(x, y, color);

        if (x == end.x && y == end.y)
            break;

        int error2 = 2 * error;

        if (error2 > -dy)
        {
            error -= dy;
            x += sx;
        }

        if (error2 < dx)
        {
            error += dx;
            y += sy;
        }
    }}
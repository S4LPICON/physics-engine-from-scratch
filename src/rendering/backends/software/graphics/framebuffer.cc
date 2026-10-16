#include <limits>
#include <algorithm>
#include <cstdint>

#include "rendering/backends/software/graphics/framebuffer.h"

uint32_t framebuffer[WIDTH * HEIGHT];
float zbuffer[WIDTH * HEIGHT];

void clearFramebuffer(uint32_t color)
{
    std::fill(
        framebuffer,
        framebuffer + (WIDTH * HEIGHT),
        color
    );
}

void clearZBuffer()
{
    std::fill(
        zbuffer,
        zbuffer + (WIDTH * HEIGHT),
        std::numeric_limits<float>::infinity()
    );
}

void drawPixel(int x, int y, uint32_t color)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;

    framebuffer[y * WIDTH + x] = color;
}
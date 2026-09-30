
#include <limits>

#include "framebuffer.h"

uint32_t framebuffer[WIDTH * HEIGHT];
float zbuffer[WIDTH * HEIGHT];

void clearFramebuffer(uint32_t color)
{
    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        framebuffer[i] = color;
        zbuffer[i] = std::numeric_limits<float>::infinity();
    }
}

void drawPixel(int x, int y, uint32_t color)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;

    framebuffer[y * WIDTH + x] = color;
}
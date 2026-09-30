#pragma once

#include <cstdint>

constexpr int WIDTH = 256;
constexpr int HEIGHT = 256;

extern uint32_t framebuffer[WIDTH * HEIGHT];

void clearFramebuffer(uint32_t color);
void putPixel(int x, int y, uint32_t color);
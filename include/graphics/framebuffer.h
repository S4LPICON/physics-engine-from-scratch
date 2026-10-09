#pragma once

#include <cstdint>

constexpr int WIDTH = 640; //640
constexpr int HEIGHT = 448; //448

extern uint32_t framebuffer[WIDTH * HEIGHT];
extern float zbuffer[WIDTH * HEIGHT];

void clearFramebuffer(uint32_t color);
void drawPixel(int x, int y, uint32_t color);
void clearZBuffer();
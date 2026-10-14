#pragma once

#include <cstdint>

constexpr int WIDTH = 800; //640
constexpr int HEIGHT = 600; //448

extern uint32_t framebuffer[WIDTH * HEIGHT];
extern float zbuffer[WIDTH * HEIGHT];

void clearFramebuffer(uint32_t color);
void clearZBuffer();
void drawPixel(int x, int y, uint32_t color);
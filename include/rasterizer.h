// rasterizer.h

#pragma once

#include <cstdint>
#include "geometry.h"

void drawPixel(int x, int y, uint32_t color);
void drawLine(Point start, Point end, uint32_t color);
void drawTriangle(const Triangle& triangle, uint32_t color);
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdint>

struct Texture {
    int width{0};
    int height{0};
    std::vector<uint32_t> pixels;

    uint32_t sample(float u, float v) const {
        if (pixels.empty() || width <= 0 || height <= 0)
            return 0xFFFFFFFF;

        u = std::clamp(u, 0.0f, 1.0f);
        v = std::clamp(v, 0.0f, 1.0f);

        const int x = std::min(static_cast<int>(u * width), width - 1);
        const int y = std::min(static_cast<int>((1.0f - v) * height), height - 1);

        return pixels[y * width + x];
    }
};

#endif 
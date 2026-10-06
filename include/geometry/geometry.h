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
        if (pixels.empty()) return 0xFFFFFFFF;

        u = u - std::floor(u);
        v = v - std::floor(v);

        int x = static_cast<int>(u * static_cast<float>(width - 1));
        int y = static_cast<int>((1.0f - v) * static_cast<float>(height - 1));

        x = std::clamp(x, 0, width - 1);
        y = std::clamp(y, 0, height - 1);

        return pixels[y * width + x];
    }
};

#endif
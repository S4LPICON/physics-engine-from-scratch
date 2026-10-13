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

        u = std::clamp(u, 0.0f, 1.0f);
        v = std::clamp(v, 0.0f, 1.0f);

        // se mapea al centro exacto del texel
        float texXf = u * static_cast<float>(width) - 0.5f;
        float texYf = (1.0f - v) * static_cast<float>(height) - 0.5f;

        int x = std::clamp(static_cast<int>(std::floor(texXf + 0.5f)), 0, width - 1);
        int y = std::clamp(static_cast<int>(std::floor(texYf + 0.5f)), 0, height - 1);

        return pixels[y * width + x];
    }
};

#endif
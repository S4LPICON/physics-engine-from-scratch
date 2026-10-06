#include "tools/texture_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

#include <iostream>

namespace TextureLoader {

Texture load(const std::string& filepath)
{
    Texture texture;
    int channels = 0;

    stbi_uc* data = stbi_load(filepath.c_str(), &texture.width, &texture.height, &channels, 4);

    if (!data) {
        std::cerr << "[ERROR] No se pudo cargar la imagen de textura: " << filepath << '\n';
        return texture;
    }

    const size_t totalPixels = static_cast<size_t>(texture.width * texture.height);
    texture.pixels.resize(totalPixels);

    for (size_t i = 0; i < totalPixels; ++i) {
        uint8_t r = data[i * 4 + 0];
        uint8_t g = data[i * 4 + 1];
        uint8_t b = data[i * 4 + 2];
        uint8_t a = data[i * 4 + 3];

        texture.pixels[i] = (static_cast<uint32_t>(a) << 24) |
                            (static_cast<uint32_t>(r) << 16) |
                            (static_cast<uint32_t>(g) << 8)  |
                            (static_cast<uint32_t>(b));
    }

    stbi_image_free(data);

    std::cout << "[INFO] Textura cargada: " << filepath 
              << " (" << texture.width << "x" << texture.height << ")\n";

    return texture;
}

}
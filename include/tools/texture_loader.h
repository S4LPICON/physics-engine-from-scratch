#pragma once

#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <string>
#include "geometry/texture.h"

namespace TextureLoader {
    /**
     * @brief Carga un archivo de imagen (PNG, JPG, BMP) y retorna una estructura Texture.
     */
    Texture load(const std::string& filepath);
}

#endif
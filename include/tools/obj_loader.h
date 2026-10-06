#pragma once

#include <string>

#include "geometry/mesh.h"

class OBJLoader {
public:
    static Mesh load(const std::string& path);
};

Mesh loadModelSafe(const std::string& path);
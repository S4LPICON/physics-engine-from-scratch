#pragma once

#include <string>

#include "resources/mesh.h"

class OBJLoader {
public:
    static Mesh load(const std::string& path);
};

Mesh loadModelSafe(const std::string& path);
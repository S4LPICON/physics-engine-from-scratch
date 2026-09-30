#pragma once

#include <string>

#include "mesh.h"

class OBJLoader {
public:
    static Mesh load(const std::string& path);
};
#pragma once

#include <vector>

struct Vertex3D {
    float x;
    float y;
    float z;
};

struct Triangle3D {
    int a;
    int b;
    int c;
};

struct Mesh {
    std::vector<Vertex3D> vertices;
    std::vector<Triangle3D> triangles;
};
#ifndef MESH_H
#define MESH_H

#include <vector>

struct Vertex3D {
    float x{0.0f}, y{0.0f}, z{0.0f};
    float u{0.0f}, v{0.0f};
};

struct Triangle3D {
    int a{-1}, b{-1}, c{-1};
};

struct Mesh {
    std::vector<Vertex3D> vertices;
    std::vector<Triangle3D> triangles;
};

#endif
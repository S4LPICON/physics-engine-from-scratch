#include "obj_loader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

Mesh OBJLoader::load(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("No se puo abrir el OBJ: " + path);
    }

    Mesh mesh;
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        std::string type;
        ss >> type;

        // Vertice
        if (type == "v")
        {
            Vertex3D vertex;

            ss >> vertex.x
               >> vertex.y
               >> vertex.z;
            
            mesh.vertices.push_back(vertex);
        }

        // Cara triangular
        else if (type == "f")
        {
            std::string a;
            std::string b;
            std::string c;

            ss >> a >> b >> c;

            Triangle3D triangle;

            triangle.a = std::stoi(a.substr(0, a.find('/'))) - 1;
            triangle.b = std::stoi(b.substr(0, b.find('/'))) - 1;
            triangle.c = std::stoi(c.substr(0, c.find('/'))) - 1;

            mesh.triangles.push_back(triangle);
        }
    }

    std::cout << "OBJ cargado: "
          << mesh.vertices.size() << " vertices, "
          << mesh.triangles.size() << " triangulos\n";

    return mesh;
}
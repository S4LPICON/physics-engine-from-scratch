#include "tools/obj_loader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <map>
#include <tuple>

namespace {

/**
 * @brief Estructura auxiliar para representar la posición 3D cruda desde el .obj
 */
struct Vec3Raw {
    float x, y, z;
};

/**
 * @brief Estructura auxiliar para representar la coordenada UV cruda desde el .obj
 */
struct Vec2Raw {
    float u, v;
};

/**
 * @brief Parsea un token de cara (ej. "1/2/3", "1//3" o "1") y extrae (vIndex, vtIndex).
 * Nota: Los índices de .obj comienzan en 1, por lo que convertimos a base 0.
 */
void parseFaceToken(const std::string& token, int& outV, int& outVT) {
    outV = -1;
    outVT = -1;

    size_t firstSlash = token.find('/');
    if (firstSlash == std::string::npos) {
        // Formato simple: "v"
        outV = std::stoi(token) - 1;
        return;
    }

    outV = std::stoi(token.substr(0, firstSlash)) - 1;

    size_t secondSlash = token.find('/', firstSlash + 1);
    std::string vtStr;

    if (secondSlash == std::string::npos) {
        // Formato: "v/vt"
        vtStr = token.substr(firstSlash + 1);
    } else {
        // Formato: "v/vt/vn"
        vtStr = token.substr(firstSlash + 1, secondSlash - firstSlash - 1);
    }

    if (!vtStr.empty()) {
        outVT = std::stoi(vtStr) - 1;
    }
}

}

Mesh OBJLoader::load(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo OBJ: " + path);
    }

    Mesh mesh;
    std::string line;

    // buffers temporales para almacenar posiciones y UVs sueltas
    std::vector<Vec3Raw> tempPositions;
    std::vector<Vec2Raw> tempUVs;

    std::map<std::pair<int, int>, int> vertexCache;

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::stringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "v")
        {
            Vec3Raw pos;
            ss >> pos.x >> pos.y >> pos.z;
            tempPositions.push_back(pos);
        }
        else if (type == "vt")
        {
            Vec2Raw uv;
            ss >> uv.u >> uv.v;
            tempUVs.push_back(uv);
        }
        // cara (f) - soporta triangulos (3), cuadrilateros (4) o n-poligonos
        else if (type == "f")
        {
            std::vector<std::string> faceTokens;
            std::string token;

            // leer TODOS los tokens de la cara presentes en la línea
            while (ss >> token) {
                faceTokens.push_back(token);
            }

            if (faceTokens.size() < 3) {
                continue; // cara invalida
            }

            std::vector<int> faceIndices;
            faceIndices.reserve(faceTokens.size());

            // procesar cada vertice de la cara
            for (const std::string& t : faceTokens)
            {
                int vIdx = -1;
                int vtIdx = -1;

                parseFaceToken(t, vIdx, vtIdx);

                if (vIdx < -1)  vIdx += static_cast<int>(tempPositions.size()) + 1;
                if (vtIdx < -1) vtIdx += static_cast<int>(tempUVs.size()) + 1;

                std::pair<int, int> lookupKey{vIdx, vtIdx};

                auto it = vertexCache.find(lookupKey);
                if (it != vertexCache.end())
                {
                    faceIndices.push_back(it->second);
                }
                else
                {
                    Vertex3D newVertex{};

                    if (vIdx >= 0 && static_cast<size_t>(vIdx) < tempPositions.size()) {
                        newVertex.x = tempPositions[vIdx].x;
                        newVertex.y = tempPositions[vIdx].y;
                        newVertex.z = tempPositions[vIdx].z;
                    }

                    if (vtIdx >= 0 && static_cast<size_t>(vtIdx) < tempUVs.size()) {
                        newVertex.u = tempUVs[vtIdx].u;
                        newVertex.v = tempUVs[vtIdx].v;
                    }

                    int newIndex = static_cast<int>(mesh.vertices.size());
                    mesh.vertices.push_back(newVertex);
                    vertexCache[lookupKey] = newIndex;

                    faceIndices.push_back(newIndex);
                }
            }

            // triangulacion en abanico (Triangle Fan):
            // si la cara tiene 3 vertices (v0, v1, v2) -> genera 1 triangulo (0, 1, 2)
            // si la cara tiene 4 vetices (v0, v1, v2, v3) -> genenra 2 triangulos (0, 1, 2) y (0, 2, 3)
            for (size_t i = 1; i + 1 < faceIndices.size(); ++i) {
                Triangle3D triangle;
                triangle.a = faceIndices[0];
                triangle.b = faceIndices[i];
                triangle.c = faceIndices[i + 1];

                mesh.triangles.push_back(triangle);
            }
        }
    }

    std::cout << "[OBJLoader] " << path << " cargado exitosamente: "
              << mesh.vertices.size() << " vértices unificados, "
              << mesh.triangles.size() << " triángulos.\n";

    return mesh;
}

/**
 * @brief Carga un modelo 3D con manejo de errores y reporte en consola.
 */
Mesh loadModelSafe(const std::string& path) 
{
    std::cout << "[INFO] Cargando modelo 3D desde: " << path << "...\n";
    Mesh mesh = OBJLoader::load(path);

    if (mesh.vertices.empty() || mesh.triangles.empty()) {
        std::cerr << "[ERROR] Fallo al cargar el modelo o archivo vacío: " << path << '\n';
    } else {
        std::cout << "[INFO] Modelo cargado exitosamente. Vértices: " 
                  << mesh.vertices.size() << " | Triángulos: " 
                  << mesh.triangles.size() << '\n';
    }

    return mesh;
}
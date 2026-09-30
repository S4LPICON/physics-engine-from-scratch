
#include "renderer3d.h"
#include "rasterizer.h"
#include "framebuffer.h"

void renderMesh3D(const Mesh& mesh)
{
    for (const Triangle3D& triangle : mesh.triangles)
    {
        if (triangle.a < 0 ||
            triangle.a >= static_cast<int>(mesh.vertices.size()) ||
            triangle.b < 0 ||
            triangle.b >= static_cast<int>(mesh.vertices.size()) ||
            triangle.c < 0 ||
            triangle.c >= static_cast<int>(mesh.vertices.size()))
        {

            continue;
        }

        Vertex3D a = mesh.vertices[triangle.a];
        Vertex3D b = mesh.vertices[triangle.b];
        Vertex3D c = mesh.vertices[triangle.c];

        a.z += 300.0f;
        b.z += 300.0f;
        c.z += 300.0f;

        if (a.z <= 1.0f ||
            b.z <= 1.0f ||
            c.z <= 1.0f)
        {
            continue;
        }

        // 3D -> perspectiva
        float ax = a.x / a.z;
        float ay = a.y / a.z;

        float bx = b.x / b.z;
        float by = b.y / b.z;

        float cx = c.x / c.z;
        float cy = c.y / c.z;

        // [-1,1] -> pantalla
        float p1ScreenX = (ax + 1.0f) * 0.5f * WIDTH;
        float p1ScreenY = (1.0f - ay) * 0.5f * HEIGHT;

        float p2ScreenX = (bx + 1.0f) * 0.5f * WIDTH;
        float p2ScreenY = (1.0f - by) * 0.5f * HEIGHT;

        float p3ScreenX = (cx + 1.0f) * 0.5f * WIDTH;
        float p3ScreenY = (1.0f - cy) * 0.5f * HEIGHT;

        // Backface culling
        float cross =
            (p2ScreenX - p1ScreenX) * (p3ScreenY - p1ScreenY)
            -
            (p2ScreenY - p1ScreenY) * (p3ScreenX - p1ScreenX);

        if (cross <= 0.0f){
            continue;}

        Triangle t{
            {
                static_cast<int>(p1ScreenX),
                static_cast<int>(p1ScreenY),
                a.z
            },
            {
                static_cast<int>(p2ScreenX),
                static_cast<int>(p2ScreenY),
                b.z
            },
            {
                static_cast<int>(p3ScreenX),
                static_cast<int>(p3ScreenY),
                c.z
            }
        };

        drawTriangle(t, 0xbbff00ff);
    }
}

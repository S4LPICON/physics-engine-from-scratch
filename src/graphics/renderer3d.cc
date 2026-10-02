#include "renderer3d.h"

#include "rasterizer.h"
#include "framebuffer.h"
#include "transform.h"

void renderMesh3D(const Mesh& mesh, const Transform& transform)
{
    Mat4 modelMatrix = transform.getMatrix();

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

        // Model space -> World space
        Vec4 aWorld =
            modelMatrix * Vec4(Vec3{a.x, a.y, a.z}, 1.0f);

        Vec4 bWorld =
            modelMatrix * Vec4(Vec3{b.x, b.y, b.z}, 1.0f);

        Vec4 cWorld =
            modelMatrix * Vec4(Vec3{c.x, c.y, c.z}, 1.0f);

        // Near clipping básico
        if (aWorld.z <= 1.0f ||
            bWorld.z <= 1.0f ||
            cWorld.z <= 1.0f)
        {
            continue;
        }

        // 3D -> perspectiva
        float ax = aWorld.x / aWorld.z;
        float ay = aWorld.y / aWorld.z;

        float bx = bWorld.x / bWorld.z;
        float by = bWorld.y / bWorld.z;

        float cx = cWorld.x / cWorld.z;
        float cy = cWorld.y / cWorld.z;

        // [-1, 1] -> pantalla
        float p1ScreenX =
            (ax + 1.0f) * 0.5f * WIDTH;

        float p1ScreenY =
            (1.0f - ay) * 0.5f * HEIGHT;

        float p2ScreenX =
            (bx + 1.0f) * 0.5f * WIDTH;

        float p2ScreenY =
            (1.0f - by) * 0.5f * HEIGHT;

        float p3ScreenX =
            (cx + 1.0f) * 0.5f * WIDTH;

        float p3ScreenY =
            (1.0f - cy) * 0.5f * HEIGHT;

        // Backface culling
        float cross =
            (p2ScreenX - p1ScreenX) *
            (p3ScreenY - p1ScreenY)
            -
            (p2ScreenY - p1ScreenY) *
            (p3ScreenX - p1ScreenX);

        if (cross <= 0.0f)
        {
            continue;
        }

        Triangle t{
            {
                static_cast<int>(p1ScreenX),
                static_cast<int>(p1ScreenY),
                aWorld.z
            },
            {
                static_cast<int>(p2ScreenX),
                static_cast<int>(p2ScreenY),
                bWorld.z
            },
            {
                static_cast<int>(p3ScreenX),
                static_cast<int>(p3ScreenY),
                cWorld.z
            }
        };

        drawTriangle(t, 0xbbff00ff);
    }
}

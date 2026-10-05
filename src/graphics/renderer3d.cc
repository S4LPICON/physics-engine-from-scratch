#include "renderer3d.h"

#include "rasterizer.h"
#include "framebuffer.h"
#include "transform.h"
#include "camera/camera.h"

void renderMesh3D(
    const Mesh& mesh,
    const Transform& transform,
    const Camera& camera)
{
    Mat4 modelMatrix = transform.getMatrix();
    Mat4 viewMatrix = camera.getViewMatrix();
    Mat4 projectionMatrix = camera.getProjectionMatrix();

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

        // World space -> View space
        Vec4 aView = viewMatrix * aWorld;
        Vec4 bView = viewMatrix * bWorld;
        Vec4 cView = viewMatrix * cWorld;

        // Near clipping básico
        if (aView.z >= -camera.nearPlane ||
            bView.z >= -camera.nearPlane ||
            cView.z >= -camera.nearPlane)
        {
            continue;
        }

        // View space -> Clip space
        Vec4 aClip = projectionMatrix * aView;
        Vec4 bClip = projectionMatrix * bView;
        Vec4 cClip = projectionMatrix * cView;

        // Perspective divide
        float ax = aClip.x / aClip.w;
        float ay = aClip.y / aClip.w;

        float bx = bClip.x / bClip.w;
        float by = bClip.y / bClip.w;

        float cx = cClip.x / cClip.w;
        float cy = cClip.y / cClip.w;

        // NDC [-1, 1] -> Screen
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

        // Depth
        float depthA = -aView.z;
        float depthB = -bView.z;
        float depthC = -cView.z;

        Triangle t{
            {
                static_cast<int>(p1ScreenX),
                static_cast<int>(p1ScreenY),
                depthA
            },

            {
                static_cast<int>(p2ScreenX),
                static_cast<int>(p2ScreenY),
                depthB
            },

            {
                static_cast<int>(p3ScreenX),
                static_cast<int>(p3ScreenY),
                depthC
            }
        };

        drawTriangle(t, 0xff0000ff);
    }
}
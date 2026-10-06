#include "graphics/renderer3d.h"

#include "graphics/rasterizer.h"
#include "graphics/framebuffer.h"
#include "geometry/transform.h"
#include "camera/camera.h"
#include "math/vec2.h"

#include <vector>
#include <algorithm>
#include <cmath>

namespace {

struct ScreenVertex {
    Vec2 position;
    float depthNDC;
    float invW;
};

struct ScreenTriangle {
    ScreenVertex v0;
    ScreenVertex v1;
    ScreenVertex v2;
};

inline Vec2 ndcToScreen(float x, float y, float width, float height) {
    return Vec2{
        (x + 1.0f) * 0.5f * width,
        (1.0f - y) * 0.5f * height
    };
}

inline float calculateSignedArea2D(const Vec2& a, const Vec2& b, const Vec2& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

}

void renderMesh3D(
    const Mesh& mesh,
    const Transform& transform,
    const Camera& camera)
{
    if (mesh.triangles.empty() || mesh.vertices.empty()) return;

    const Mat4 modelMatrix      = transform.getMatrix();
    const Mat4 viewMatrix       = camera.getViewMatrix();
    const Mat4 projectionMatrix = camera.getProjectionMatrix();
    const Mat4 mvpMatrix        = projectionMatrix * viewMatrix * modelMatrix;

    const float screenWidth  = static_cast<float>(WIDTH);
    const float screenHeight = static_cast<float>(HEIGHT);

    const size_t vertexCount = mesh.vertices.size();

    for (const Triangle3D& tri : mesh.triangles)
    {
        if (tri.a < 0 || static_cast<size_t>(tri.a) >= vertexCount ||
            tri.b < 0 || static_cast<size_t>(tri.b) >= vertexCount ||
            tri.c < 0 || static_cast<size_t>(tri.c) >= vertexCount)
        {
            continue;
        }

        const Vertex3D& vA = mesh.vertices[tri.a];
        const Vertex3D& vB = mesh.vertices[tri.b];
        const Vertex3D& vC = mesh.vertices[tri.c];

        Vec4 aClip = mvpMatrix * Vec4(vA.x, vA.y, vA.z, 1.0f);
        Vec4 bClip = mvpMatrix * Vec4(vB.x, vB.y, vB.z, 1.0f);
        Vec4 cClip = mvpMatrix * Vec4(vC.x, vC.y, vC.z, 1.0f);

        if (aClip.w <= camera.nearPlane || 
            bClip.w <= camera.nearPlane || 
            cClip.w <= camera.nearPlane)
        {
            continue;
        }

        const float invWA = 1.0f / aClip.w;
        const float invWB = 1.0f / bClip.w;
        const float invWC = 1.0f / cClip.w;

        const Vec3 aNDC{ aClip.x * invWA, aClip.y * invWA, aClip.z * invWA };
        const Vec3 bNDC{ bClip.x * invWB, bClip.y * invWB, bClip.z * invWB };
        const Vec3 cNDC{ cClip.x * invWC, cClip.y * invWC, cClip.z * invWC };

        const Vec2 pA = ndcToScreen(aNDC.x, aNDC.y, screenWidth, screenHeight);
        const Vec2 pB = ndcToScreen(bNDC.x, bNDC.y, screenWidth, screenHeight);
        const Vec2 pC = ndcToScreen(cNDC.x, cNDC.y, screenWidth, screenHeight);

        const float crossProduct = calculateSignedArea2D(pA, pB, pC);

        Triangle renderTri{
            { static_cast<int>(pA.x), static_cast<int>(pA.y), aNDC.z },
            { static_cast<int>(pB.x), static_cast<int>(pB.y), bNDC.z },
            { static_cast<int>(pC.x), static_cast<int>(pC.y), cNDC.z }
        };

        const uint32_t surfaceColor = (crossProduct > 0.0f) ? 0x0000FFFF : 0xFF0000FF;
        drawTriangle(renderTri, surfaceColor);
    }
}


void renderMesh3DTextured(
    const Mesh& mesh,
    const Transform& transform,
    const Camera& camera,
    const Texture& texture)
{
    if (mesh.triangles.empty() || mesh.vertices.empty()) {
        return;
    }

    const Mat4 modelMatrix      = transform.getMatrix();
    const Mat4 viewMatrix       = camera.getViewMatrix();
    const Mat4 projectionMatrix = camera.getProjectionMatrix();
    const Mat4 mvpMatrix        = projectionMatrix * viewMatrix * modelMatrix;

    const float screenWidth  = static_cast<float>(WIDTH);
    const float screenHeight = static_cast<float>(HEIGHT);

    std::vector<ScreenTriangle> visibleTriangles;
    visibleTriangles.reserve(mesh.triangles.size());

    const size_t vertexCount = mesh.vertices.size();

    for (const Triangle3D& tri : mesh.triangles)
    {
        if (tri.a < 0 || static_cast<size_t>(tri.a) >= vertexCount ||
            tri.b < 0 || static_cast<size_t>(tri.b) >= vertexCount ||
            tri.c < 0 || static_cast<size_t>(tri.c) >= vertexCount)
        {
            continue;
        }

        const Vertex3D& vA = mesh.vertices[tri.a];
        const Vertex3D& vB = mesh.vertices[tri.b];
        const Vertex3D& vC = mesh.vertices[tri.c];

        Vec4 aClip = mvpMatrix * Vec4(vA.x, vA.y, vA.z, 1.0f);
        Vec4 bClip = mvpMatrix * Vec4(vB.x, vB.y, vB.z, 1.0f);
        Vec4 cClip = mvpMatrix * Vec4(vC.x, vC.y, vC.z, 1.0f);

        if (aClip.w <= camera.nearPlane || 
            bClip.w <= camera.nearPlane || 
            cClip.w <= camera.nearPlane)
        {
            continue;
        }

        const float invWA = 1.0f / aClip.w;
        const float invWB = 1.0f / bClip.w;
        const float invWC = 1.0f / cClip.w;

        const Vec3 aNDC{ aClip.x * invWA, aClip.y * invWA, aClip.z * invWA };
        const Vec3 bNDC{ bClip.x * invWB, bClip.y * invWB, bClip.z * invWB };
        const Vec3 cNDC{ cClip.x * invWC, cClip.y * invWC, cClip.z * invWC };

        const Vec2 pA = ndcToScreen(aNDC.x, aNDC.y, screenWidth, screenHeight);
        const Vec2 pB = ndcToScreen(bNDC.x, bNDC.y, screenWidth, screenHeight);
        const Vec2 pC = ndcToScreen(cNDC.x, cNDC.y, screenWidth, screenHeight);

        const float crossProduct = calculateSignedArea2D(pA, pB, pC);
        if (crossProduct <= 0.0f) {
            continue;
        }

        Point3D renderA{
            static_cast<int>(pA.x), static_cast<int>(pA.y), aNDC.z,
            vA.u * invWA, vA.v * invWA, invWA
        };

        Point3D renderB{
            static_cast<int>(pB.x), static_cast<int>(pB.y), bNDC.z,
            vB.u * invWB, vB.v * invWB, invWB
        };

        Point3D renderC{
            static_cast<int>(pC.x), static_cast<int>(pC.y), cNDC.z,
            vC.u * invWC, vC.v * invWC, invWC
        };

        drawTexturedTriangle(renderA, renderB, renderC, texture);

        visibleTriangles.push_back(ScreenTriangle{
            { pA, aNDC.z, invWA },
            { pB, bNDC.z, invWB },
            { pC, cNDC.z, invWC }
        });
    }

    constexpr uint32_t WIREFRAME_COLOR = 0x555555FF;

    for (const ScreenTriangle& tri : visibleTriangles)
    {
        Point3D pA{ static_cast<int>(tri.v0.position.x), static_cast<int>(tri.v0.position.y), tri.v0.depthNDC, 0.0f, 0.0f, tri.v0.invW };
        Point3D pB{ static_cast<int>(tri.v1.position.x), static_cast<int>(tri.v1.position.y), tri.v1.depthNDC, 0.0f, 0.0f, tri.v1.invW };
        Point3D pC{ static_cast<int>(tri.v2.position.x), static_cast<int>(tri.v2.position.y), tri.v2.depthNDC, 0.0f, 0.0f, tri.v2.invW };

        drawLineDepth(pA, pB, WIREFRAME_COLOR);
        drawLineDepth(pB, pC, WIREFRAME_COLOR);
        drawLineDepth(pC, pA, WIREFRAME_COLOR);
    }
}
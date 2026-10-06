#pragma once

#include "geometry/mesh.h"
#include "geometry/transform.h"
#include "camera/camera.h"
#include "geometry/geometry.h"

void renderMesh3DTextured(const Mesh& mesh, const Transform& transform, const Camera& camera, const Texture& texture);
void renderMesh3D(const Mesh& mesh, const Transform& transform, const Camera& camera);
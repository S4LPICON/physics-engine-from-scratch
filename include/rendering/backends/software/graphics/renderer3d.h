#pragma once

#include "resources/mesh.h"
#include "resources/transform.h"
#include "engine/objects/camera/camera.h"
#include "resources/texture.h"

void renderMesh3DTextured(const Mesh& mesh, const Transform& transform, const Camera& camera, const Texture& texture);
void renderMesh3D(const Mesh& mesh, const Transform& transform, const Camera& camera);
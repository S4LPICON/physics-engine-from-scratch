#pragma once

#include "mesh.h"
#include "transform.h"
#include "camera/camera.h"

void renderMesh3D(const Mesh& mesh, const Transform& transform, const Camera& camera);
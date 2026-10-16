#pragma once

#include "collider_component.h"
#include "math/vec3.h"

class BoxCollider : public ColliderComponent
{
private:
    Vec3 size;

public:
    BoxCollider(const Vec3& size);

    ~BoxCollider() override;

    const Vec3& getSize() const;
};
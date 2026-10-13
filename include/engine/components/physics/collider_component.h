
#pragma once

#include "engine/components/component.h"
#include "math/vec3.h"

class ColliderComponent : public Component
{
private:
    float radius;

public:
    explicit ColliderComponent(float radius = 0.5f);

    float getRadius() const;
    void setRadius(float radius);

    Vec3 getWorldCenter() const;
};

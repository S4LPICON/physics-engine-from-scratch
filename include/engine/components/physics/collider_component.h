
#pragma once

#include "engine/components/component.h"
#include "math/vec3.h"

class ColliderComponent : public Component
{
private:
public:
    ColliderComponent();
    Vec3 getWorldCenter() const;
};

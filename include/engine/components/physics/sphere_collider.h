#pragma once

#include "collider_component.h"

class SphereCollider : public ColliderComponent
{
private:
    float radius;
public:
    SphereCollider(float radius);
    ~SphereCollider();
    float getRadius() const;
    void setRadius(float radius);
};

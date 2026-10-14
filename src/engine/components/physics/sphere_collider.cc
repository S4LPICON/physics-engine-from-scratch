#include "engine/components/physics/sphere_collider.h"



SphereCollider::SphereCollider(float radius)
    : radius(radius > 0.0f ? radius : 0.5f)
{
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::setRadius(float radius)
{
    this->radius = radius;
}

float SphereCollider::getRadius() const
{
    return radius;
}
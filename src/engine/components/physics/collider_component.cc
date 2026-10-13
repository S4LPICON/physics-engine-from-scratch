
#include "engine/components/physics/collider_component.h"

ColliderComponent::ColliderComponent(float radius)
    : radius(radius > 0.0f ? radius : 0.5f)
{
}

float ColliderComponent::getRadius() const
{
    return radius;
}

void ColliderComponent::setRadius(float radius)
{
    if (radius > 0.0f)
    {
        this->radius = radius;
    }
}

Vec3 ColliderComponent::getWorldCenter() const
{
    if (gameObject == nullptr)
    {
        return Vec3{0.0f, 0.0f, 0.0f};
    }

    return gameObject->getTransform().position;
}

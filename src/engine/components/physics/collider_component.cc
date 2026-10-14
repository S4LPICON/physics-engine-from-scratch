
#include "engine/components/physics/collider_component.h"

ColliderComponent::ColliderComponent()
{
    
}

Vec3 ColliderComponent::getWorldCenter() const
{
    if (gameObject == nullptr)
    {
        return Vec3{0.0f, 0.0f, 0.0f};
    }

    return gameObject->getTransform().position;
}

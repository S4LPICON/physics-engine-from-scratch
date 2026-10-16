#include "engine/components/physics/box_collider.h"

BoxCollider::BoxCollider(const Vec3& size)
    : size(size)
{
}

BoxCollider::~BoxCollider() = default;

const Vec3& BoxCollider::getSize() const
{
    return size;
}
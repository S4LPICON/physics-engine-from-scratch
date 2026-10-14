
#include "engine/physics/CollisionSystem.h"

#include "engine/components/physics/collider_component.h"
#include "engine/components/physics/sphere_collider.h"
#include "engine/objects/generic/game_object.h"
#include "engine/objects/generic/scene.h"

#include "rendering/backends/software/graphics/renderer3d.h"

#include <iostream>
#include <vector>

namespace
{
    struct ColliderEntry
    {
        GameObject* owner;
        SphereCollider* collider;
    };

    bool checkCollision(
        const SphereCollider& a,
        const SphereCollider& b)
    {
        const Vec3 centerA = a.getWorldCenter();
        const Vec3 centerB = b.getWorldCenter();

        const float dx = centerA.x - centerB.x;
        const float dy = centerA.y - centerB.y;
        const float dz = centerA.z - centerB.z;

        const float distanceSquared =
            dx * dx + dy * dy + dz * dz;

        const float radiusSum = a.getRadius() + b.getRadius();

        return distanceSquared <= radiusSum * radiusSum;
    }
}

void detectCollisions(Scene* scene)
{
    if (scene == nullptr)
    {
        return;
    }

    std::vector<ColliderEntry> colliders;

    // 1. Recopilar todos los colliders de la escena.
    for (const auto& gameObject : scene->getObjects())
    {
        if (!gameObject)
        {
            continue;
        }

        auto components =
            gameObject->getComponents<SphereCollider>();

        for (auto* collider : components)
        {

            renderDebugSphere(
                collider->getWorldCenter(),
                1.0f,
                *scene->getCamera(),
                0xFF00FF00
            );
            
            colliders.push_back({
                gameObject.get(),
                collider
            });
        }
    }

    // 2. Comparar cada pareja una sola vez.
    for (std::size_t i = 0; i < colliders.size(); ++i)
    {
        for (std::size_t j = i + 1; j < colliders.size(); ++j)
        {
            const auto& a = colliders[i];
            const auto& b = colliders[j];

            // Un objeto no colisiona consigo mismo.
            if (a.owner == b.owner)
            {
                continue;
            }

            // 3. Comprobar si sus esferas se superponen.
            if (checkCollision(*a.collider, *b.collider))
            {
                std::cout
                    << "Collision detected between objects "
                    << i << " and " << j << '\n';
            }
        }
    }
}

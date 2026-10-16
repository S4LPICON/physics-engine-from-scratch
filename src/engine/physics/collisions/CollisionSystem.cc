
#include "engine/physics/CollisionSystem.h"

#include "engine/components/physics/collider_component.h"
#include "engine/components/physics/sphere_collider.h"
#include "engine/components/physics/box_collider.h"
#include "engine/components/script_component.h"

#include "engine/objects/generic/game_object.h"
#include "engine/objects/generic/scene.h"

#include "rendering/backends/software/graphics/renderer3d.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <unordered_set>
#include <utility>
#include <vector>

namespace
{
    enum class ColliderType
    {
        Sphere,
        Box
    };

    enum class CollisionEventType
    {
        Enter,
        Stay,
        Exit
    };

    struct ColliderEntry
    {
        GameObject* owner;
        ColliderType type;
        ColliderComponent* collider;
    };

    struct CollisionPair
    {
        ColliderEntry a;
        ColliderEntry b;
    };

    struct PairKey
    {
        ColliderComponent* a;
        ColliderComponent* b;

        bool operator==(const PairKey& other) const
        {
            return a == other.a && b == other.b;
        }
    };

    struct PairKeyHash
    {
        std::size_t operator()(const PairKey& key) const
        {
            const std::size_t h1 =
                std::hash<ColliderComponent*>{}(key.a);

            const std::size_t h2 =
                std::hash<ColliderComponent*>{}(key.b);

            return h1 ^ (
                h2 + static_cast<std::size_t>(0x9e3779b9)
                + (h1 << 6) + (h1 >> 2)
            );
        }
    };

    using CollisionSet = std::unordered_set<PairKey, PairKeyHash>;

    PairKey makePairKey(
        ColliderComponent* a,
        ColliderComponent* b)
    {
        if (std::less<ColliderComponent*>{}(b, a))
        {
            std::swap(a, b);
        }

        return {a, b};
    }

    CollisionPair makePair(ColliderEntry a, ColliderEntry b)
    {
        if (std::less<ColliderComponent*>{}(
                b.collider, a.collider))
        {
            std::swap(a, b);
        }

        return {a, b};
    }

    void dispatchCollision(
        GameObject* owner,
        ColliderComponent* other,
        CollisionEventType eventType)
    {
        if (owner == nullptr)
        {
            return;
        }

        for (auto* script : owner->getComponents<ScriptComponent>())
        {
            switch (eventType)
            {
                case CollisionEventType::Enter:
                    script->onCollisionEnter(other);
                    break;

                case CollisionEventType::Stay:
                    script->onCollisionStay(other);
                    break;

                case CollisionEventType::Exit:
                    script->onCollisionExit(other);
                    break;
            }
        }
    }

    void dispatchPair(
        const CollisionPair& pair,
        CollisionEventType eventType)
    {
        dispatchCollision(
            pair.a.owner,
            pair.b.collider,
            eventType
        );

        dispatchCollision(
            pair.b.owner,
            pair.a.collider,
            eventType
        );
    }

    bool checkCollision(
        const SphereCollider& sphere,
        const BoxCollider& box)
    {
        const Vec3 center = sphere.getWorldCenter();
        const float radius = sphere.getRadius();

        const Vec3 boxCenter = box.getWorldCenter();
        const Vec3 size = box.getSize();

        const Vec3 half{
            size.x * 0.5f,
            size.y * 0.5f,
            size.z * 0.5f
        };

        const Vec3 closest{
            std::clamp(
                center.x,
                boxCenter.x - half.x,
                boxCenter.x + half.x
            ),
            std::clamp(
                center.y,
                boxCenter.y - half.y,
                boxCenter.y + half.y
            ),
            std::clamp(
                center.z,
                boxCenter.z - half.z,
                boxCenter.z + half.z
            )
        };

        const float dx = center.x - closest.x;
        const float dy = center.y - closest.y;
        const float dz = center.z - closest.z;

        const float distanceSquared =
            dx * dx + dy * dy + dz * dz;

        return distanceSquared <= radius * radius;
    }

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

    bool checkCollision(
        const BoxCollider& a,
        const BoxCollider& b)
    {
        const Vec3 centerA = a.getWorldCenter();
        const Vec3 centerB = b.getWorldCenter();

        const Vec3 sizeA = a.getSize();
        const Vec3 sizeB = b.getSize();

        const Vec3 halfA{
            sizeA.x * 0.5f,
            sizeA.y * 0.5f,
            sizeA.z * 0.5f
        };

        const Vec3 halfB{
            sizeB.x * 0.5f,
            sizeB.y * 0.5f,
            sizeB.z * 0.5f
        };

        return
            std::abs(centerA.x - centerB.x) <= halfA.x + halfB.x &&
            std::abs(centerA.y - centerB.y) <= halfA.y + halfB.y &&
            std::abs(centerA.z - centerB.z) <= halfA.z + halfB.z;
    }

    bool checkCollision(
        const ColliderEntry& a,
        const ColliderEntry& b)
    {
        if (a.type == ColliderType::Sphere &&
            b.type == ColliderType::Sphere)
        {
            return checkCollision(
                *static_cast<SphereCollider*>(a.collider),
                *static_cast<SphereCollider*>(b.collider)
            );
        }

        if (a.type == ColliderType::Box &&
            b.type == ColliderType::Box)
        {
            return checkCollision(
                *static_cast<BoxCollider*>(a.collider),
                *static_cast<BoxCollider*>(b.collider)
            );
        }

        if (a.type == ColliderType::Sphere &&
            b.type == ColliderType::Box)
        {
            return checkCollision(
                *static_cast<SphereCollider*>(a.collider),
                *static_cast<BoxCollider*>(b.collider)
            );
        }

        if (a.type == ColliderType::Box &&
            b.type == ColliderType::Sphere)
        {
            return checkCollision(
                *static_cast<SphereCollider*>(b.collider),
                *static_cast<BoxCollider*>(a.collider)
            );
        }

        return false;
    }
}

void detectCollisions(Scene* scene)
{
    if (scene == nullptr)
    {
        return;
    }

    std::vector<ColliderEntry> colliders;

    static std::vector<CollisionPair> previousCollisions;

    static CollisionSet previousKeys;

    const auto& objects = scene->getObjects();
    colliders.reserve(objects.size() * 2);

    const auto* camera = scene->getCamera();

    for (const auto& gameObject : objects)
    {
        if (!gameObject)
        {
            continue;
        }

        for (auto* collider :
             gameObject->getComponents<SphereCollider>())
        {
            if (camera != nullptr)
            {
                renderDebugSphere(
                    collider->getWorldCenter(),
                    collider->getRadius(),
                    *camera,
                    0xFF00FF00
                );
            }

            colliders.push_back({
                gameObject.get(),
                ColliderType::Sphere,
                collider
            });
        }

        for (auto* collider :
             gameObject->getComponents<BoxCollider>())
        {
            if (camera != nullptr)
            {
                renderDebugBox(
                    collider->getWorldCenter(),
                    collider->getSize(),
                    *camera,
                    0xFF00FF00
                );
            }

            colliders.push_back({
                gameObject.get(),
                ColliderType::Box,
                collider
            });
        }
    }

    const std::size_t n = colliders.size();
    const std::size_t maxPairs = n > 1 ? n * (n - 1) / 2 : 0;

    std::vector<CollisionPair> currentCollisions;
    currentCollisions.reserve(
        std::min(maxPairs, previousCollisions.size() + n)
    );

    CollisionSet currentKeys;
    currentKeys.reserve(
        std::min(maxPairs, previousKeys.size() + n)
    );

    for (std::size_t i = 0; i < n; ++i)
    {
        const auto& a = colliders[i];

        for (std::size_t j = i + 1; j < n; ++j)
        {
            const auto& b = colliders[j];

            if (a.owner == b.owner)
            {
                continue;
            }

            if (!checkCollision(a, b))
            {
                continue;
            }

            CollisionPair pair = makePair(a, b);
            const PairKey key{
                pair.a.collider,
                pair.b.collider
            };

            currentCollisions.push_back(pair);
            currentKeys.insert(key);

            const CollisionEventType eventType =
                previousKeys.find(key) == previousKeys.end()
                    ? CollisionEventType::Enter
                    : CollisionEventType::Stay;

            dispatchPair(pair, eventType);
        }
    }

    for (const auto& previous : previousCollisions)
    {
        const PairKey key{
            previous.a.collider,
            previous.b.collider
        };

        if (currentKeys.find(key) == currentKeys.end())
        {
            dispatchPair(previous, CollisionEventType::Exit);
        }
    }

    previousCollisions = std::move(currentCollisions);
    previousKeys = std::move(currentKeys);
}

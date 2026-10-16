
#pragma once

#include "engine/components/script_component.h"
#include "engine/components/physics/collider_component.h"

class CollisionTestScript : public ScriptComponent
{
public:
    void update(float dt) override;

    void onCollisionEnter(ColliderComponent* other) override;
    void onCollisionStay(ColliderComponent* other) override;
    void onCollisionExit(ColliderComponent* other) override;
};

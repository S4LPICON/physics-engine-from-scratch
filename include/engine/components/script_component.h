#pragma once

#include "engine/components/component.h"

class ColliderComponent;

class ScriptComponent : public Component
{
private:
    bool initialized = false;

public:
    virtual void start() {}

    virtual void update(float dt) override = 0;

    virtual void onCollisionEnter(ColliderComponent* other) {}
    virtual void onCollisionStay(ColliderComponent* other) {}
    virtual void onCollisionExit(ColliderComponent* other) {}

    void execute(float dt)
    {
        if (!initialized)
        {
            start();
            initialized = true;
        }

        update(dt);
    }
};

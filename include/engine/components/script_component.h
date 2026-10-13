#pragma once

#include "engine/components/component.h"

class ScriptComponent : public Component
{
private:
    bool initialized = false;

public:
    virtual void start() {}
    virtual void update(float dt) override = 0;

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
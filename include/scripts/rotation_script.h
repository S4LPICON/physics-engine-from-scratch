#pragma once

#include "engine/components/script_component.h"

class RotationScript : public ScriptComponent
{
public:
    void start() override;

    void update(float dt) override;
};
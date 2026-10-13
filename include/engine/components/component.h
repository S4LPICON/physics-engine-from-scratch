#pragma once

#include "engine/objects/generic/game_object.h"

class Component 
{
protected:
    GameObject* gameObject = nullptr;

public:
    virtual ~Component() = default;

    virtual void update(float dt) {}

    void setGameObject(GameObject* owner)
    {
        gameObject = owner;
    }
};

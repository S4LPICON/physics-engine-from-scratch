
#include "scripts/rotation_script.h"

#include <iostream>

bool llendo = false;

void RotationScript::start()
{
    std::cout << "Hello from the method start of the rotation script\n";
}

void RotationScript::update(float dt)
{
    gameObject->getTransform().rotation.y += 1.0f * dt;

    if (gameObject->getTransform().position.x >= 30.0f)
    {
        llendo = false;
    }
    else if (gameObject->getTransform().position.x < 0.0f)
    {
        llendo = true;
    }

    if (llendo)
    {
        gameObject->getTransform().position.x += 2.0f * dt;
    }
    else
    {
        gameObject->getTransform().position.x -= 2.0f * dt;
    }
}
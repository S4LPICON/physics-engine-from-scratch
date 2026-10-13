
#include "scripts/t_script.h"

#include <iostream>

bool llendo1 = false;

void TScript::start()
{
    std::cout << "Hello from the method start of the rotation script\n";
}

void TScript::update(float dt)
{
    gameObject->getTransform().rotation.y += 1.0f * dt;

    if (gameObject->getTransform().position.x >= 30.0f)
    {
        llendo1 = true;
    }
    else if (gameObject->getTransform().position.x < 0.0f)
    {
        llendo1 = false;
    }

    if (llendo1)
    {
        gameObject->getTransform().position.x -= 2.0f * dt;
    }
    else
    {
        gameObject->getTransform().position.x += 2.0f * dt;
    }
}

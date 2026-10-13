#include "scripts/rotation_script.h"

#include <iostream>

void RotationScript::start()
{
     std::cout << "Hello from the method start of the rotation script\n";
}

void RotationScript::update(float dt)
{
    gameObject->getTransform().rotation.y += 1 * dt;
}

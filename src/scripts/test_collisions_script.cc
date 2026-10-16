
#include "scripts/test_collisions_script.h"

#include <iostream>

void CollisionTestScript::update(float dt)
{
    (void)dt;
}

void CollisionTestScript::onCollisionEnter(ColliderComponent* other)
{
    std::cout << "Colision iniciada: " << other << '\n';
}

void CollisionTestScript::onCollisionStay(ColliderComponent* other)
{
    // mientras estan colisionando se ejecuta esto
    (void)other;
}

void CollisionTestScript::onCollisionExit(ColliderComponent* other)
{
    std::cout << "Colision terminada: " << other << '\n';
}

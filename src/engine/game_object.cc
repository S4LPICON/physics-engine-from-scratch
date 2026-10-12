#include "engine/game_object.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

Transform& GameObject::getTransform()
{
    return transform;
}
#include "engine/objects/generic/game_object.h"
#include "engine/components/component.h"

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

void GameObject::addComponent(std::unique_ptr<Component> component)
{
    component->setGameObject(this);
    components.push_back(std::move(component));
}
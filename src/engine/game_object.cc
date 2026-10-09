#include "engine/game_object.h"

GameObject::GameObject() {
    transform.position = {0.0f, 0.0f, 0.0f};
    transform.rotation = {0.0f, 0.0f, 0.0f};
    transform.scale    = {1.0f, 1.0f, 1.0f};
}

void GameObject::addComponent(std::unique_ptr<Component> component) {
    components.push_back(std::move(component));
}

void GameObject::update(float dt){
    for (auto& component : components) {
        component->update(dt);
    }
}
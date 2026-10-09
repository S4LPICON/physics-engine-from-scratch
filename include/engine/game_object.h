#pragma once

#include <memory>
#include <vector>

#include "components/component.h"
#include "geometry/transform.h"

class GameObject {
public:
    Transform transform;
    std::vector<std::unique_ptr<Component>> components;
    GameObject();

    void addComponent(std::unique_ptr<Component> component);
    void update(float dt);

private:
    
};

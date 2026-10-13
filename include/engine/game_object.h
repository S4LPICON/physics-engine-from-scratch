#pragma once

#include <vector>
#include <memory>
#include <type_traits>

#include "geometry/transform.h"

class Component;

class GameObject
{
private:
    Transform transform;
    std::vector<std::unique_ptr<Component>> components;

public:
    GameObject();
    ~GameObject();

    Transform& getTransform();

    void addComponent(std::unique_ptr<Component> component);

    template <typename T>
    std::vector<T*> getComponents()
    {
        std::vector<T*> result;

        for (const auto& component : components)
        {
            if (auto* casted = dynamic_cast<T*>(component.get()))
            {
                result.push_back(casted);
            }
        }

        return result;
    }
};
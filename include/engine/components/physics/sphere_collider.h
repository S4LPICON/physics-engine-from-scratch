#pragma once

#include "collider_component.h"

class SphereCollider : public ColliderComponent
{
private:
    float radio;
public:
    SphereCollider(/* args */);
    ~SphereCollider();

    void setRadio(float radio);
};

#pragma once

#include "geometry/mesh.h"
#include "geometry/texture.h"
#include "geometry/transform.h"

class GameObject
{
private:
    Transform transform;
    //vector de componentes
public:
    
    GameObject();
    ~GameObject();
    Transform& getTransform();
    //get objecst -> un template para cualquier tipo generico
    //set object --||>
};
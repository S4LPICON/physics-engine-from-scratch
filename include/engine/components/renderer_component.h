// renderer_component.h
#pragma once

#include "component.h"
#include "geometry/mesh.h"
#include "geometry/texture.h"
#include "camera/camera.h"

class RendererComponent : public Component {

private:
    Mesh* modelMesh;
    Texture* texture;
    Camera* camera;
public:

    RendererComponent(Mesh* modelMesh, Texture* texture, Camera* camera);
    
    void update(float dt) override;
};

//necesitamos:
// el model -> se carga ya
// el transform -> lo podemos agarra del gameobject padre
// textura -> se carga] ya
//camera -> el metodo la agarra de alguna manera?
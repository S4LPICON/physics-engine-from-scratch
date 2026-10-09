// renderer_component.cc

//necesitamos:
// el model -> se carga
// el transform -> lo podemos inicializar el 0
// textura -> se carga]
//camera -> el metodo la agarra de alguna manera?

#include "engine/components/renderer_component.h"
#include "graphics/renderer3d.h"

Transform transform{
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {1.0f, 1.0f, 1.0f}
};

RendererComponent::RendererComponent(Mesh* modelMesh, Texture* texture, Camera* camera)
    : modelMesh(modelMesh),
      texture(texture),
      camera(camera)
{
}

void RendererComponent::update(float dt) {
    renderMesh3DTextured(*RendererComponent::modelMesh, transform, *camera,  *RendererComponent::texture);
}
#include "components/renderer_component.h"

#include "geometry/mesh.h"
#include "geometry/texture.h"


RendererComponent::RendererComponent(Mesh* mesh, Texture* texture)
    :mesh(mesh), texture(texture)
{
}

RendererComponent::~RendererComponent()
{
}

Mesh* RendererComponent::getMesh() const
{
    return mesh;
}

void RendererComponent::setMesh(Mesh* mesh)
{
    this->mesh = mesh;
}

Texture* RendererComponent::getTexture() const
{
    return texture;
}

void RendererComponent::setTexture(Texture* texture)
{
    this->texture = texture;
}
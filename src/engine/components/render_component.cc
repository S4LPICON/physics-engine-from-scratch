#include "engine/components/renderer_component.h"

#include "resources/mesh.h"
#include "resources/texture.h"


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
#pragma once

#include "components/component.h"

class Mesh;
class Texture;

class RendererComponent : public Component
{
private:
    Mesh* mesh = nullptr;
    Texture* texture = nullptr;

public:
    RendererComponent();
    ~RendererComponent() override;

    void setMesh(Mesh* mesh);
    void setTexture(Texture* texture);

    Mesh* getMesh() const;
    Texture* getTexture() const;
};
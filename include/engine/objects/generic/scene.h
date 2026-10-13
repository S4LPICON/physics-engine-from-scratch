#pragma once

#include <vector>
#include <memory>
#include "engine/objects/generic/game_object.h"
#include "engine/objects/camera/camera.h"


class Scene
{
private:
    Camera* camera = nullptr;
    std::vector<std::unique_ptr<GameObject>> objects;
public:
    Scene();
    ~Scene();
    void setCamera(Camera* camera);
    Camera* getCamera() const;
    Camera* getModifiableCamera(); // temp
    void addGameObject(std::unique_ptr<GameObject> gameObject);
    const std::vector<std::unique_ptr<GameObject>>& getObjects() const;
};

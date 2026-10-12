#pragma once

#include <vector>
#include <memory>
#include "game_object.h"
#include "camera/camera.h"


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
    void addGameObject(std::unique_ptr<GameObject> gameObject);
    const std::vector<std::unique_ptr<GameObject>>& getObjects() const;
};

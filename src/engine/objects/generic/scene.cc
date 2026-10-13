
#include "engine/objects/generic/scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::setCamera(Camera* camera)
{
    Scene::camera = camera;
}

void Scene::addGameObject(std::unique_ptr<GameObject> gameObject)
{
    objects.push_back(std::move(gameObject));
}

const std::vector<std::unique_ptr<GameObject>>& Scene::getObjects() const
{
    return objects;
}

Camera* Scene::getCamera() const
{
    return camera;
}

Camera* Scene::getModifiableCamera()
{
    return camera;
}
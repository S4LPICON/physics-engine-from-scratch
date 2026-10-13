#include "engine/core/engine.h"

#include "scripts/rotation_script.h"
#include "scripts/t_script.h"

#include "engine/components/physics/sphere_collider.h"

int main(int argc, char* argv[])
{
    Mesh model = OBJLoader::load("assets/models/sphere.obj");
    Texture texture = TextureLoader::load("assets/models/sphere.png");

    //Mesh model2 = OBJLoader::load("assets/test2.obj");
    //Texture texture2 = TextureLoader::load("assets/text2.png");

    // camera
    Camera camera;

    Scene scene;
    scene.setCamera(&camera);

    //###gameobject1
    auto gameObject = std::make_unique<GameObject>();

    //gameObject->getTransform().scale = {30.0f, 2.0f, 30.0f};

    auto renderComponent =
        std::make_unique<RendererComponent>(&model, &texture);

    

    auto rotScript = std::make_unique<RotationScript>();

    auto collider = std::make_unique<SphereCollider>();
    collider->setRadius(3.0f);

    gameObject->addComponent(std::move(renderComponent));
    gameObject->addComponent(std::move(rotScript));
    gameObject->addComponent(std::move(collider));


    //-----------------------------

    //####### gameobject2
    auto gameObject2 = std::make_unique<GameObject>();
    gameObject2->getTransform().position.x = 37.0f;

    auto renderComponent2 =
        std::make_unique<RendererComponent>(&model, &texture);

    auto rotScript2 = std::make_unique<TScript>();
    auto collider2 = std::make_unique<SphereCollider>();
    collider2->setRadius(3.0f);
    gameObject2->addComponent(std::move(renderComponent2));
    gameObject2->addComponent(std::move(rotScript2));
    gameObject2->addComponent(std::move(collider2));
    //----------------------------------

    scene.addGameObject(std::move(gameObject));
    scene.addGameObject(std::move(gameObject2));

  //  scene.addGameObject();

    Engine engine;
    engine.init();
    engine.loadScene(&scene);
    engine.run();
    engine.stop();


    return 0;
}
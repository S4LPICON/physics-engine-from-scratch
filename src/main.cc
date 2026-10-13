#include "engine/core/engine.h"

#include "scripts/rotation_script.h"

int main(int argc, char* argv[])
{
    Mesh model = OBJLoader::load("assets/test1.obj");
    Texture texture = TextureLoader::load("assets/text1.png");

    Mesh model2 = OBJLoader::load("assets/test2.obj");
    Texture texture2 = TextureLoader::load("assets/text2.png");

    // camera
    Camera camera;

    Scene scene;
    scene.setCamera(&camera);

    //###gameobject1
    auto gameObject = std::make_unique<GameObject>();

    auto renderComponent =
        std::make_unique<RendererComponent>(&model, &texture);

    auto rotScript = std::make_unique<RotationScript>();

    gameObject->addComponent(std::move(renderComponent));
    gameObject->addComponent(std::move(rotScript));

    //-----------------------------

    //####### gameobject2
    auto gameObject2 = std::make_unique<GameObject>();
    gameObject2->getTransform().position.x = 37.0f;

    auto renderComponent2 =
        std::make_unique<RendererComponent>(&model2, &texture2);

    auto rotScript2 = std::make_unique<RotationScript>();

    gameObject2->addComponent(std::move(renderComponent2));
    gameObject2->addComponent(std::move(rotScript2));
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
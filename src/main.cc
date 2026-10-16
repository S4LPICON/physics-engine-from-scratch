#include "engine/core/engine.h"

#include "scripts/rotation_script.h"
#include "scripts/t_script.h"

#include "engine/components/physics/sphere_collider.h"
#include "engine/components/physics/box_collider.h"

#include "scripts/test_collisions_script.h"


int main(int argc, char* argv[])
{
    Mesh model = OBJLoader::load("assets/models/sphere.obj");
    Texture texture = TextureLoader::load("assets/models/sphere.png");

    Mesh model2 = OBJLoader::load("assets/test/platform.obj");
    Texture texture2 = TextureLoader::load("assets/test/texture.png");

    // camera
    Camera camera;

    Scene scene;
    scene.setCamera(&camera);

    //###gameobject1
    auto gameObject = std::make_unique<GameObject>();
    gameObject->getTransform().position.y = 3.0f;
    //gameObject->getTransform().scale = {30.0f, 2.0f, 30.0f};

    auto renderComponent =
        std::make_unique<RendererComponent>(&model, &texture);

    

    auto rotScript = std::make_unique<RotationScript>();
    auto testcollisionsscript = std::make_unique<CollisionTestScript>();
    

    auto collider = std::make_unique<SphereCollider>(1.0f);
   // auto collider = std::make_unique<BoxCollider>(
   //     Vec3{1.0f, 1.0f, 1.0f}
  //  );

    gameObject->addComponent(std::move(renderComponent));
    //gameObject->addComponent(std::move(rotScript));
    gameObject->addComponent(std::move(collider));
    gameObject->addComponent(std::move(testcollisionsscript));


    //-----------------------------
    auto gameObjectplane = std::make_unique<GameObject>();
    auto renderComponentplane =
        std::make_unique<RendererComponent>(&model2, &texture2);

    gameObjectplane->addComponent(std::move(renderComponentplane));


    //####### gameobject2
    auto gameObject2 = std::make_unique<GameObject>();
    gameObject2->getTransform().position.x = 2.0f;
    gameObject2->getTransform().position.z = 5.0f;
    gameObject2->getTransform().position.y = 2.0f;

    auto renderComponent2 =
        std::make_unique<RendererComponent>(&model, &texture);

    auto rotScript2 = std::make_unique<TScript>();
    auto collider2 = std::make_unique<BoxCollider>(
        Vec3{1.0f, 1.0f, 1.0f}
    );
    gameObject2->addComponent(std::move(renderComponent2));
    //gameObject2->addComponent(std::move(rotScript2));
    gameObject2->addComponent(std::move(collider2));
    //----------------------------------

    scene.addGameObject(std::move(gameObject));
    scene.addGameObject(std::move(gameObject2));
    scene.addGameObject(std::move(gameObjectplane));

  //  scene.addGameObject();

    Engine engine;
    engine.init();
    engine.loadScene(&scene);
    engine.run();
    engine.stop();


    return 0;
}
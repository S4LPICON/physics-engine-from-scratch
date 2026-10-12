#include "include/engine.h"
#include "include/tools/obj_loader.h"
#include "include/tools/texture_loader.h"
#include "include/geometry/texture.h"


int main()
{
    Mesh model = OBJLoader::load("assets/pollo.obj");
    Texture texture = TextureLoader::load("assets/test.png");

    // camera
    Camera camera;

    Scene scene;
    scene.setCamera(&camera);

    scene.addGameObject(
        std::make_unique<GameObject>(&model, &texture) //changed to a component system
    );

    Engine engine;
    engine.init();
    engine.loadScene(&scene);
    engine.run();
    engine.stop();


    return 0;
}
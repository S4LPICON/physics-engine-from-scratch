#include <iostream>

#include "rendering/backends/software/software_renderer.h"

#include "engine/core/engine.h"
#include "engine/events/events.h"
#include "engine/time/s4time.h"
#include "engine/pipelines/renderer_pipeline.h"
#include "engine/pipelines/object_update_pipeline.h"

Engine::Engine(){}
Engine::~Engine(){}

const int MOVE_SPEED = 10;
const int ROTATION_SPEED = 10;


void Engine::init()
{

    window     = createWindow();
    renderer = createRenderer(window);
    texture   = createTexture(renderer);

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "[FATAL] Fallo al inicializar SDL3: " << SDL_GetError() << '\n';
        return;
    }

    if (!window || !renderer || !texture) {
        std::cerr << "[FATAL] Error al crear contexto grafico de SDL3.\n";
        SDL_Quit();
        return;
    }
}


void Engine::run(){
    //verificar que haya una escena cargada
    if (Engine::scene == nullptr)
    {
        std::cerr << "[FATAL] no hay escena para cargar.\n";
        return;
    }
    
    while (processEvents())
    {
        Time::update();
        deltaTime = Time::deltaTime();
        clearFramebuffer(0xFFFFFFFF);
        clearZBuffer();
        //physics pipeline (future)
        //renderer pipeline
        startUpdateObjectsPipeline(*scene, deltaTime);
        startRenderScenePipeline(*scene, deltaTime);
        auto camera = scene->getModifiableCamera();
        tempCameraController(*camera, input, deltaTime);

        updateTexture(texture, framebuffer);
        drawFramebuffer(renderer, texture);
    }
}

void tempCameraController(Camera& camera, const Input& input, float deltaTime)
{
    // inputs
        if (input.isKeyDown(Key::Space)) {
            camera.position.y += MOVE_SPEED * deltaTime;
        }
        if (input.isKeyDown(Key::Shift)) {
            camera.position.y -= MOVE_SPEED * deltaTime;
        }

        if (input.isKeyDown(Key::A)) {
            camera.position.x -= MOVE_SPEED * deltaTime;
        }
        if (input.isKeyDown(Key::D)) {
            camera.position.x += MOVE_SPEED * deltaTime;
        }

        if (input.isKeyDown(Key::W)) {
            camera.position.z -= MOVE_SPEED * deltaTime;
        }
        if (input.isKeyDown(Key::S)) {
            camera.position.z += MOVE_SPEED * deltaTime;
        }

        if (input.isKeyDown(Key::Left)) {
            camera.rotation.y += ROTATION_SPEED * deltaTime;
        }
        if (input.isKeyDown(Key::Right)) {
            camera.rotation.y -= ROTATION_SPEED * deltaTime;
        }

        if (input.isKeyDown(Key::Up)) {
            camera.rotation.x += ROTATION_SPEED * deltaTime;
        }
        if (input.isKeyDown(Key::Down)) {
            camera.rotation.x -= ROTATION_SPEED * deltaTime;
        }
}

void Engine::stop()
{
    destroyRenderer(renderer, texture);
    destroyWindow(window);

    SDL_Quit();
}


void Engine::loadScene(Scene* scene)
{
    Engine::scene = scene;
}
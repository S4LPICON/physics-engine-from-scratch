#include <iostream>

#include "rendering/backends/software/software_renderer.h"

#include "engine/core/engine.h"
#include "engine/events/events.h"
#include "engine/time/s4time.h"
#include "engine/pipelines/renderer_pipeline.h"
#include "engine/pipelines/object_update_pipeline.h"

#include "engine/physics/CollisionSystem.h"

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

#include <chrono>
#include <iostream>

void Engine::run()
{
    if (scene == nullptr)
    {
        std::cerr << "[FATAL] no hay escena para cargar.\n";
        return;
    }

    using Clock = std::chrono::steady_clock;

    auto lastFPSUpdate = Clock::now();
    int frameCount = 0;

    while (processEvents())
    {
        Time::update();
        deltaTime = Time::deltaTime();

        // Contador de FPS
        frameCount++;

        auto now = Clock::now();
        auto elapsed = std::chrono::duration<float>(
            now - lastFPSUpdate
        ).count();

        if (elapsed >= 1.0f)
        {
            std::cout << "FPS: "
                      << frameCount / elapsed
                      << '\n';

            frameCount = 0;
            lastFPSUpdate = now;
        }

        clearFramebuffer(0xFFFFFFFF);
        clearZBuffer();

        detectCollisions(scene);

        startUpdateObjectsPipeline(*scene, deltaTime);
        startRenderScenePipeline(*scene, deltaTime);

        auto camera = scene->getModifiableCamera();
        tempCameraController(*camera, input, deltaTime);

        updateTexture(texture, framebuffer);
        drawFramebuffer(renderer, texture);
    }
}

#include <cmath>

void tempCameraController(Camera& camera, const Input& input, float deltaTime)
{
    // Dirección horizontal de la cámara
    float yaw = camera.rotation.y;

    Vec3 forward{
        -std::sin(yaw),
        0.0f,
        -std::cos(yaw)
    };

    Vec3 right{
        std::cos(yaw),
        0.0f,
        -std::sin(yaw)
    };

    // Movimiento vertical
    if (input.isKeyDown(Key::Space)) {
        camera.position.y += MOVE_SPEED * deltaTime;
    }
    if (input.isKeyDown(Key::Shift)) {
        camera.position.y -= MOVE_SPEED * deltaTime;
    }

    // Movimiento relativo a la cámara
    if (input.isKeyDown(Key::W)) {
        camera.position.x += forward.x * MOVE_SPEED * deltaTime;
        camera.position.z += forward.z * MOVE_SPEED * deltaTime;
    }
    if (input.isKeyDown(Key::S)) {
        camera.position.x -= forward.x * MOVE_SPEED * deltaTime;
        camera.position.z -= forward.z * MOVE_SPEED * deltaTime;
    }
    if (input.isKeyDown(Key::D)) {
        camera.position.x += right.x * MOVE_SPEED * deltaTime;
        camera.position.z += right.z * MOVE_SPEED * deltaTime;
    }
    if (input.isKeyDown(Key::A)) {
        camera.position.x -= right.x * MOVE_SPEED * deltaTime;
        camera.position.z -= right.z * MOVE_SPEED * deltaTime;
    }

    // Rotación horizontal
    if (input.isKeyDown(Key::Left)) {
        camera.rotation.y += ROTATION_SPEED * deltaTime;
    }
    if (input.isKeyDown(Key::Right)) {
        camera.rotation.y -= ROTATION_SPEED * deltaTime;
    }

    // Rotación vertical
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
#include <cmath>
#include <iostream>
#include <utility>

#include "rendering/backends/software/software_renderer.h"

#include "engine/core/engine.h"
#include "engine/core/debug/profiler.h"
#include "engine/events/events.h"
#include "engine/time/s4time.h"
#include "engine/pipelines/renderer_pipeline.h"
#include "engine/pipelines/object_update_pipeline.h"
#include "engine/physics/CollisionSystem.h"

Engine::Engine(){}
Engine::~Engine(){}

const int MOVE_SPEED = 10;
const int ROTATION_SPEED = 10;

template <typename Function>
    void measureIfEnabled(
        Profiler& profiler,
        bool enabled,
        Profiler::Stage stage,
        Function&& function)
    {
        if (enabled)
        {
            profiler.measure(
                stage,
                std::forward<Function>(function)
            );
        }
        else
        {
            std::forward<Function>(function)();
        }
}


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

void Engine::run()
{
    if (scene == nullptr)
    {
        std::cerr << "[FATAL] no hay escena para cargar.\n";
        return;
    }

    Profiler profiler;

    bool f3WasDown = false;

    while (processEvents())
    {
        Time::update();
        deltaTime = Time::deltaTime();

        // toggle profiler -> F3
        const bool f3IsDown = input.isKeyDown(Key::F3);

        if (f3IsDown && !f3WasDown)
        {
            profilerEnabled = !profilerEnabled;

            std::cout << "[Profiler] "
                      << (profilerEnabled ? "ACTIVADO" : "DESACTIVADO")
                      << '\n';
        }

        f3WasDown = f3IsDown;

        measureIfEnabled(
            profiler,
            profilerEnabled,
            Profiler::Stage::FrameTotal,
            [&]()
            {
                measureIfEnabled(
                    profiler, profilerEnabled,
                    Profiler::Stage::ClearFramebuffer,
                    [&]()
                    {
                        clearFramebuffer(0xFFFFFFFF);
                    }
                );

                measureIfEnabled(
                    profiler, profilerEnabled,
                    Profiler::Stage::ClearZBuffer,
                    [&]()
                    {
                        clearZBuffer();
                    }
                );

                measureIfEnabled(
                    profiler, profilerEnabled,
                    Profiler::Stage::Collisions,
                    [&]()
                    {
                        detectCollisions(scene);
                    }
                );

                measureIfEnabled(
                    profiler, profilerEnabled,
                    Profiler::Stage::UpdatePipeline,
                    [&]()
                    {
                        startUpdateObjectsPipeline(*scene, deltaTime);
                    }
                );

                measureIfEnabled(
                    profiler, profilerEnabled,
                    Profiler::Stage::RenderPipeline,
                    [&]()
                    {
                        startRenderScenePipeline(*scene, deltaTime);
                    }
                );

                measureIfEnabled(
                    profiler, profilerEnabled,
                    Profiler::Stage::CameraController,
                    [&]()
                    {
                        auto camera = scene->getModifiableCamera();

                        if (camera != nullptr)
                        {
                            tempCameraController(
                                *camera, input, deltaTime
                            );
                        }
                    }
                );

                measureIfEnabled(
                    profiler, profilerEnabled,
                    Profiler::Stage::SDLUpload,
                    [&]()
                    {
                        updateTexture(texture, framebuffer);
                    }
                );

                measureIfEnabled(
                    profiler, profilerEnabled,
                    Profiler::Stage::SDLPresent,
                    [&]()
                    {
                        drawFramebuffer(renderer, texture);
                    }
                );
            }
        );

        if (profilerEnabled)
        {
            profiler.endFrame();
        }
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
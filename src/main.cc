#include <SDL3/SDL.h>
#include <iostream>
#include <string>

#include "graphics/framebuffer.h"
#include "graphics/window.h"
#include "graphics/renderer.h"
#include "events/events.h"
#include "tools/obj_loader.h"
#include "graphics/renderer3d.h"

#include "graphics/rasterizer.h"
#include "time/time.h"
#include "input/input.h"
#include "camera/camera.h"
#include "tools/texture_loader.h"
#include "tools/obj_loader.h"
#include "engine/game_object.h"

#include "engine/components/renderer_component.h"

constexpr float MOVE_SPEED = 15.0f; // unidades por segundo
constexpr float FOV_SPEED  = 30.0f; // grados por segundp
constexpr float ROTATION_SPEED = 7.0f; // unidades por segundo



bool Init_Engine(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Texture*& texture) 
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "[FATAL] Fallo al inicializar SDL3: "
                  << SDL_GetError() << '\n';
        return false;
    }

    window = createWindow();
    if (!window) {
        std::cerr << "[FATAL] Error al crear la ventana.\n";
        SDL_Quit();
        return false;
    }

    renderer = createRenderer(window);
    if (!renderer) {
        std::cerr << "[FATAL] Error al crear el renderer.\n";
        destroyWindow(window);
        SDL_Quit();
        return false;
    }

    texture = createTexture(renderer);
    if (!texture) {
        std::cerr << "[FATAL] Error al crear la textura.\n";
        destroyRenderer(renderer, nullptr);
        destroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

void handleInput(const Input& input, Camera& camera, int moveSpeed, float dt )
{
    // inputs
        if (input.isKeyDown(Key::Space)) {
            camera.position.y += MOVE_SPEED * dt;
        }
        if (input.isKeyDown(Key::Shift)) {
            camera.position.y -= MOVE_SPEED * dt;
        }

        if (input.isKeyDown(Key::A)) {
            camera.position.x -= MOVE_SPEED * dt;
        }
        if (input.isKeyDown(Key::D)) {
            camera.position.x += MOVE_SPEED * dt;
        }

        if (input.isKeyDown(Key::W)) {
            camera.position.z -= MOVE_SPEED * dt;
        }
        if (input.isKeyDown(Key::S)) {
            camera.position.z += MOVE_SPEED * dt;
        }

        if (input.isKeyDown(Key::Left)) {
            camera.rotation.y += ROTATION_SPEED * dt;
        }
        if (input.isKeyDown(Key::Right)) {
            camera.rotation.y -= ROTATION_SPEED * dt;
        }

        if (input.isKeyDown(Key::Up)) {
            camera.rotation.x += ROTATION_SPEED * dt;
        }
        if (input.isKeyDown(Key::Down)) {
            camera.rotation.x -= ROTATION_SPEED * dt;
        }
}

int main()
{

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;

    if (!Init_Engine(window, renderer, texture)) {
        return -1;
    }
    
    // camera
    Input input;
    Camera camera;
    GameObject object;
    Mesh model = loadModelSafe("assets/cat.obj");
    Mesh model2 = loadModelSafe("assets/mtest.obj");
    Texture modelTexture = TextureLoader::load("assets/waoos.png");

    object.addComponent(
        std::make_unique<RendererComponent>(&model, &modelTexture, &camera)
    );

    while (processEvents())
    {
        Time::update();
        const float dt = Time::deltaTime();

        handleInput(input, camera, MOVE_SPEED, dt);
        
        //clean buffers
        clearFramebuffer(0xFFFFFFFF);
        clearZBuffer();

        object.update(dt);

        updateTexture(texture, framebuffer);
        drawFramebuffer(renderer, texture);
    }

    destroyRenderer(renderer, texture);
    destroyWindow(window);

    SDL_Quit();
}
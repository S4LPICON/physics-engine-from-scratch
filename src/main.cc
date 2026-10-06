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

constexpr float MOVE_SPEED = 15.0f; // unidades por segundo
constexpr float FOV_SPEED  = 30.0f; // grados por segundp
constexpr float ROTATION_SPEED = 7.0f; // unidades por segundo

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "[FATAL] Fallo al inicializar SDL3: " << SDL_GetError() << '\n';
        return -1;
    }

    SDL_Window* window     = createWindow();
    SDL_Renderer* renderer = createRenderer(window);
    SDL_Texture* texture   = createTexture(renderer);

    if (!window || !renderer || !texture) {
        std::cerr << "[FATAL] Error al crear contexto grafico de SDL3.\n";
        SDL_Quit();
        return -1;
    }

    Mesh model = loadModelSafe("assets/test.obj");
    Input input;
    Texture modelTexture = TextureLoader::load("assets/test.png");
    
    // transformacion por defecto para el objeto
    Transform transform;
    transform.position = {0.0f, 0.0f, -30.0f};
    transform.rotation = {0.0f, 0.5f, 0.0f};
    transform.scale    = {2.0f, 2.0f, 2.0f};

    // camera
    Camera camera;
    camera.fov         = 70.0f;
    camera.aspectRatio = static_cast<float>(WIDTH) / static_cast<float>(HEIGHT);
    camera.nearPlane   = 0.1f;
    camera.farPlane    = 1000.0f;

    while (processEvents())
    {
        Time::update();
        const float dt = Time::deltaTime();

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

        clearFramebuffer(0xFFFFFFFF);
        
        // limpiar zbuffer
        std::fill(zbuffer, zbuffer + (WIDTH * HEIGHT), 1000.0f);

        //rontando el modelo
        transform.rotation.y += 2.0f * dt;

        // render mesh (con teztura)
        renderMesh3DTextured(model, transform, camera, modelTexture);
        //renderMesh3D(model, transform, camera);

        updateTexture(texture, framebuffer);
        drawFramebuffer(renderer, texture);
    }

    destroyRenderer(renderer, texture);
    destroyWindow(window);

    SDL_Quit();
}
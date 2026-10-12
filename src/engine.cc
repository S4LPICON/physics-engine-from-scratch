#include <iostream>

#include "engine.h"
#include "graphics/window.h"
#include "graphics/renderer.h"
#include "graphics/renderer3d.h"
#include "events/events.h"
#include "graphics/framebuffer.h"
#include "time/s4time.h"

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
        

        updateTexture(texture, framebuffer);
        drawFramebuffer(renderer, texture);
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
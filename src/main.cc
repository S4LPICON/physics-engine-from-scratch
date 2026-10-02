#include <SDL3/SDL.h>
#include <iostream>

#include "framebuffer.h"
#include "window.h"
#include "renderer.h"
#include "events.h"
#include "obj_loader.h"
#include "renderer3d.h"

#include "rasterizer.h"
#include "time/time.h"
#include "input.h"


Triangle near{
    {500, 300, 100.0f},
    {700, 500, 100.0f},
    {300, 500, 100.0f}
};

Triangle far{
    {500, 300, 200.0f},
    {700, 500, 200.0f},
    {300, 500, 200.0f}
};

void debug(const Mesh& cube)
{
        std::cout << "Vertices: " << cube.vertices.size() << '\n';
        std::cout << "Triangles: " << cube.triangles.size() << '\n';

        float minZ = cube.vertices[0].z;
        float maxZ = cube.vertices[0].z;

        for (const Vertex3D& v : cube.vertices) {
            minZ = std::min(minZ, v.z);
            maxZ = std::max(maxZ, v.z);
        }

        std::cout << "Z min: " << minZ << '\n';
        std::cout << "Z max: " << maxZ << '\n';

}

Mesh loadModel(const std::string& path) 
{
    std::cout << "Intentando cargar modelo " << path << '\n';

    return OBJLoader::load(path);
}


int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = createWindow();
    SDL_Renderer* renderer = createRenderer(window);
    SDL_Texture* texture = createTexture(renderer);

    Mesh model = loadModel("assets/cat.obj");
    Input input;
    Transform transform;

    transform.position = {0.0f, 0.0f, 300.0f};
    transform.rotation = {0.0f, 0.5f, 0.0f};
    transform.scale = {2.0f, 2.0f, 2.0f};

    while (processEvents())
    {
        Time::update();

        if (input.isKeyDown(Key::A))
        {
            transform.position.x -= 1.0f;
        }

        if (input.isKeyDown(Key::D))
        {
            transform.position.x += 1.0f;
        }

        if (input.isKeyDown(Key::W))
        {
            transform.position.z -= 1.0f;
        }

        if (input.isKeyDown(Key::S))
        {
            transform.position.z += 1.0f;
        }

        clearFramebuffer(0x000000FF);

        drawTriangle(near, 0xFFFFFFFF);
        drawTriangle(far, 0x00FF22FF);

        //debug(model);
        
        transform.rotation.y += 2.0f * Time::deltaTime();
        renderMesh3D(model, transform);


        updateTexture(texture, framebuffer);
        drawFramebuffer(renderer, texture);
    }

    destroyRenderer(renderer, texture);
    destroyWindow(window);

    SDL_Quit();
}
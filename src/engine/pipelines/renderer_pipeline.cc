#include "engine/pipelines/renderer_pipeline.h"

#include "engine/scene.h"

void startRenderScenePipeline(const Scene& scene)
{
    //este pipeline se encarga de renderizar en pantalla todos los objectos de la escena
    if (scene.getCamera() == nullptr)
    {
        //no hay camara en donde mostrar
        return;
    }

    if (scene.getObjects().empty()) // tenemos que mirar que hayan objectos con componentes renderer en la escena
    {
        //no hay que renderizar
        return;
    }
    
    
}

/*

antes renderizaba asi:

for (const auto& gameObject : Engine::scene->getObjects())
        {
            gameObject->getTransform().rotation.y += 1 * deltaTime;
            renderMesh3DTextured(*gameObject->getMesh(),
                 gameObject->getTransform(),
                *camera,
                *gameObject->getTexture());
        }
*/
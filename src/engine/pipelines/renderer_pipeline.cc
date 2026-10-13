#include "engine/pipelines/renderer_pipeline.h"

#include <iostream>
#include "engine/scene.h"
#include "graphics/renderer3d.h"
#include "components/renderer_component.h"

void startRenderScenePipeline(const Scene& scene, float deltaTime)
{
    //este pipeline se encarga de renderizar en pantalla todos los objectos de la escena
    if (scene.getCamera() == nullptr)
    {
        //no hay camara en donde mostrar
        std::cerr << "[FATAL] no camera.\n";
        return;
    }

    if (scene.getObjects().empty()) // tenemos que mirar que hayan objectos con componentes renderer en la escena
    {
        //no hay que renderizar
        std::cerr << "[FATAL] no objetos.\n";
        return;
    }
    auto* actualCamera = scene.getCamera();
    for (const auto& gameObject : scene.getObjects())
    {
        auto renderers =
            gameObject->getComponents<RendererComponent>();

        for (const auto* renderer : renderers)
        {
            renderMesh3DTextured(*renderer->getMesh(),
            gameObject->getTransform(),
            *actualCamera,
            *renderer->getTexture());
            // Renderizar usando el transform del GameObject.
        }
    }
}
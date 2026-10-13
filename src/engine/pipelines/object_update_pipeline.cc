#include "engine/pipelines/object_update_pipeline.h"
#include "engine/objects/generic/scene.h"
#include "engine/components/script_component.h"
#include <iostream>

void startUpdateObjectsPipeline(const Scene& scene, float deltaTime)
{

    if (scene.getObjects().empty()) // tenemos que mirar que hayan objectos con componentes  en la escena
    {
        //no hay que actualizar
        std::cerr << "[FATAL] no objetos.\n";
        return;
    }


    for (const auto& gameObject : scene.getObjects())
    {
        auto toUpdate = gameObject->getComponents<ScriptComponent>();

        for (auto* updatable : toUpdate)
        {
            updatable->execute(deltaTime);
        }
    }
}
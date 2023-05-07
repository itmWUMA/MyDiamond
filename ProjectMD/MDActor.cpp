#include "MDActor.h"

#include "MDSceneComponent.h"

MDActor::MDActor()
{
    SceneComponent = make_shared<MDSceneComponent>();
}

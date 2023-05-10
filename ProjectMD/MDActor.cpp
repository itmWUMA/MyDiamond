#include "MDActor.h"

#include "MDDebugger.h"
#include "MDScene.h"
#include "MDSceneComponent.h"

MDActor::MDActor()
{
    SceneComponent = make_shared<MDSceneComponent>();
}

shared_ptr<MDActor> MDActor::GetSideActor(EMoveDirection Direction) const
{
    Vector2D Offset(0, 0);
    switch (Direction)
    {
    case EMoveDirection::UP:
        Offset.second = -1;
        break;
    case EMoveDirection::RIGHT:
        Offset.first = 1;
        break;
    case EMoveDirection::DOWN:
        Offset.second = 1;
        break;
    case EMoveDirection::LEFT:
        Offset.first = -1;
        break;
    default:
        break;
    }

    const Vector2D CurPosition = SceneComponent->GetVector();
    const Vector2D TargetPosition = Vector2D(CurPosition.first + Offset.first, CurPosition.second + Offset.second);
    if (!MDScene::Get()->CheckActorPosition(TargetPosition))
    {
        return nullptr;
    }

    return MDScene::Get()->GetActorByPosition(TargetPosition);
}

#include "MDPawn.h"
#include "MDDefines.h"
#include "MDDebugger.h"
#include "MDMovementComponent.h"
#include "MDPlayerState.h"
#include "MDRenderComponent.h"
#include "MDScene.h"
#include "MDSceneComponent.h"

MDPawn::MDPawn(char Texture) : Texture(Texture), PlayerState(nullptr)
{
    RenderComponent = make_shared<MDRenderComponent>();
    MovementComponent = make_shared<MDMovementComponent>();
}

MDPawn::~MDPawn()
{
#if _DEBUG
    MDDebugger::Log(DEBUG_FUNC_SIGN);
#endif
}

MDPawn::MDPawn(char Texture, const shared_ptr<MDPlayerState>& PlayerState)
    : MDPawn(Texture)
{
    InitPawn(PlayerState);
}

void MDPawn::InitPawn(const shared_ptr<MDPlayerState>& PlayerStateIns)
{
    this->PlayerState = PlayerStateIns;
    if (PlayerState)
    {
        SceneComponent->SetVector(PlayerState->GetDefaultSpawnPosition());
    }

    MDScene::Get()->RegisterActor(shared_from_this());
}

void MDPawn::Move(EMoveDirection Direction)
{
    MDScene* Scene = MDScene::Get();

    // if not registered, which means the actor is not exist in the scene
    if (!Scene->CheckRegister(this))
    {
        return;
    }

    const Vector2D CurPosition = SceneComponent->GetVector();
    const Vector2D NewPosition = MovementComponent->Move(CurPosition, Direction);

    if (!MDScene::Get()->CheckActorPosition(NewPosition))
    {
        return;
    }

    SceneComponent->SetVector(NewPosition);
    Scene->UpdateSlots();
}

void MDPawn::Render() const
{
    MDActor::Render();

    RenderComponent->Render(Texture);
}

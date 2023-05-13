#include "MDDiamond.h"

#include "MDDebugger.h"
#include "MDDefines.h"
#include "MDGameMode.h"
#include "MDGameState.h"
#include "MDMovementComponent.h"
#include "MDRenderComponent.h"
#include "MDScene.h"
#include "MDSceneComponent.h"

MDDiamond::MDDiamond()
{
    RenderComponent = make_shared<MDRenderComponent>();
    MovementComponent = make_shared<MDMovementComponent>();
}

MDDiamond::~MDDiamond()
{
#if _DEBUG
    MDDebugger::Log(DEBUG_FUNC_SIGN);
#endif 
}

MDDiamond::MDDiamond(char Texture, EDiamondType DiamondType)
    : Texture(Texture), DiamondType(DiamondType)
{
    RenderComponent = make_shared<MDRenderComponent>();
    MovementComponent = make_shared<MDMovementComponent>();
}

void MDDiamond::Render() const
{
    MDActor::Render();

    RenderComponent->Render(Texture);
}

void MDDiamond::Move(EMoveDirection Direction)
{
    Move(Direction, MovementComponent->GetStep());
}

void MDDiamond::Move(EMoveDirection Direction, int Step)
{
    MDScene* Scene = MDScene::Get();

    // if not registered, which means the actor is not exist in the scene
    if (!Scene->CheckRegister(this))
    {
        return;
    }

    const Vector2D CurPosition = SceneComponent->GetVector();
    const Vector2D NewPosition = MovementComponent->Move(CurPosition, Direction, Step);

    if (!MDScene::Get()->CheckActorPosition(NewPosition))
    {
        return;
    }

    SceneComponent->SetVector(NewPosition);
    Scene->UpdateSlots();
}

void MDDiamond::MoveToPosition(Vector2D TargetPosition)
{
    MDScene* Scene = MDScene::Get();

    // if not registered, which means the actor is not exist in the scene
    if (!Scene->CheckRegister(this))
    {
        return;
    }

    if (!Scene->CheckActorPosition(TargetPosition))
    {
        return;
    }

    SceneComponent->SetVector(TargetPosition);
    Scene->UpdateSlots();
}

bool MDDiamond::IsMeetingDeadLine() const
{
    const shared_ptr<MDGameState> GameState = GameInstance->GetGameMode()->GetGameState();
    if (GameState)
    {
        return SceneComponent->GetX() >= GameState->GetDeadLine();
    }

    return false;
}
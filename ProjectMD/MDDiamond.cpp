#include "MDDiamond.h"
#include "MDDefines.h"
#include "MDGameMode.h"
#include "MDGameState.h"
#include "MDMovementComponent.h"
#include "MDRenderComponent.h"
#include "MDScene.h"
#include "MDSceneComponent.h"

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

void MDDiamond::Eliminate(EDiamondType EliminateType)
{
    const shared_ptr<MDGameMode> GameMode = MDScene::Get()->GetGameMode();
    if (!GameMode)
    {
        return;
    }
    const shared_ptr<MDGameState> GameState = GameMode->GetGameState();

    int Count = FindAllEliminatedDiamond(EliminateType, GameState);
}

int MDDiamond::FindAllEliminatedDiamond(EDiamondType EliminateType, const shared_ptr<MDGameState>& GameState)
{
    if (!GameState)
    {
        return 0;
    }

    if (EliminateType != this->DiamondType)
    {
        return 0;
    }

    const int ResultCount = GameState->EliminatedDiamondSet.count(this);
    if (ResultCount > 0)
    {
        return 0;
    }

    GameState->EliminatedDiamondSet.insert(this);

    // All eliminated diamonds need to check their neighborhood and do the same thing
    return 1 + CheckNeighborhood(EliminateType, GameState, EMoveDirection::UP)
        + CheckNeighborhood(EliminateType, GameState, EMoveDirection::RIGHT)
        + CheckNeighborhood(EliminateType, GameState, EMoveDirection::DOWN)
        + CheckNeighborhood(EliminateType, GameState, EMoveDirection::LEFT);
}

int MDDiamond::CheckNeighborhood(EDiamondType EliminateType, const shared_ptr<MDGameState>& GameState, EMoveDirection CheckDirection) const
{
    const shared_ptr<MDDiamond> UpDiamond = dynamic_pointer_cast<MDDiamond>(GetSideActor(CheckDirection));

    if (UpDiamond)
    {
        return UpDiamond->FindAllEliminatedDiamond(EliminateType, GameState);
    }

    return 0;
}

#include "MDPawn.h"
#include "MDDefines.h"
#include "MDDebugger.h"
#include "MDDiamond.h"
#include "MDGameState.h"
#include "MDMovementComponent.h"
#include "MDPlayerState.h"
#include "MDRenderComponent.h"
#include "MDScene.h"
#include "MDSceneComponent.h"

MDPawn::MDPawn(const json11::Json& ConfigJson) : PlayerState(nullptr)
{
    RenderComponent = make_shared<MDRenderComponent>();
    MovementComponent = make_shared<MDMovementComponent>();

    if (CheckConfig(ConfigJson))
    {
        Texture = ConfigJson["Texture"].string_value().at(0);
    }
}

MDPawn::~MDPawn()
{
#if _DEBUG
    MDDebugger::Log(DEBUG_FUNC_SIGN);
#endif
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

void MDPawn::Move(EMoveDirection Direction) const
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

void MDPawn::Grab() const
{
    Vector2D OutPosition;
    const bool bResult = GetUpperActorPosition(OutPosition);
    if (!bResult)
    {
        return;
    }

    MDScene* Scene = MDScene::Get();
    const shared_ptr<MDDiamond> TargetDiamond =
        dynamic_pointer_cast<MDDiamond>(Scene->GetActorByPosition(OutPosition));
    if (!TargetDiamond)
    {
        return;
    }

    PlayerState->AcquiredDiamond = TargetDiamond;
    Scene->UnRegisterActor(TargetDiamond);
}

void MDPawn::Throw() const
{
    Vector2D OutPosition;
    const bool bResult = GetUpperActorPosition(OutPosition);
    const Vector2D TargetPosition = bResult ?
        Vector2D(OutPosition.first + 1, OutPosition.second) : Vector2D(0, SceneComponent->GetY());

    MDScene* Scene = MDScene::Get();
    const shared_ptr<MDDiamond> AcquiredDiamond = PlayerState->AcquiredDiamond;
    AcquiredDiamond->SceneComponent->SetVector(TargetPosition);

    if (AcquiredDiamond->IsMeetingDeadLine())
    {
        const shared_ptr<MDGameState> GameState = GameInstance->GetGameMode()->GetGameState();
        if (GameState)
        {
            GameState->SetGameOver();
        }
        return;
    }

    Scene->RegisterActor(AcquiredDiamond);
    PlayerState->AcquiredDiamond = nullptr;

    // elimination
    MDDiamondUtilities::EliminateDiamonds(AcquiredDiamond, AcquiredDiamond->GetType());
}

void MDPawn::Render() const
{
    MDActor::Render();

    RenderComponent->Render(Texture);
}

bool MDPawn::GetUpperActorPosition(Vector2D& OutPosition) const
{
    const MDScene* Scene = MDScene::Get();
    const int CurX = SceneComponent->GetX();
    const int CurY = SceneComponent->GetY();

    for (int i = CurX - 1; i >= 0; --i)
    {
        shared_ptr<MDActor> Slot = Scene->GetActorByPosition(i, CurY);
        if (Slot)
        {
            OutPosition = Slot->SceneComponent->GetVector();
            return true;
        }
    }

    return false;
}

bool MDPawn::CheckConfig(const json11::Json& ConfigJson)
{
    return ConfigJson["Texture"].is_string();
}

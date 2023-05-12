#include "MDDiamondUtilities.h"
#include "MDDefines.h"
#include "MDDiamond.h"
#include "MDGameState.h"
#include "MDGameMode.h"
#include "MDScene.h"
#include "MDActor.h"
#include "MDPlayerState.h"
#include "MDSceneComponent.h"

void MDDiamondUtilities::EliminateDiamonds(const shared_ptr<MDDiamond>& EntryDiamond, EDiamondType EliminateType)
{
    const shared_ptr<MDGameMode> GameMode = MDScene::Get()->GetGameMode();
    if (!GameMode)
    {
        return;
    }

    const shared_ptr<MDGameState> GameState = GameMode->GetGameState();
    if (!GameState)
    {
        return;
    }

    const float EntryDiamondScore = EntryDiamond->Score;
    const int Count = FindAllEliminatedDiamond(EntryDiamond, EliminateType, GameState);
    if (Count > 1)
    {
        EliminateDiamondsFromRecordSet(GameState->GetEliminatedDiamondSet());

        // update player's score
        const shared_ptr<MDPlayerState> PlayerState = GameMode->GetPlayerState();
        if (PlayerState)
        {
            PlayerState->Score += static_cast<float>(Count) * EntryDiamondScore;
        }
    }

    GameState->GetEliminatedDiamondSet().clear();
}

int MDDiamondUtilities::FindAllEliminatedDiamond(const shared_ptr<MDDiamond>& EntryDiamond, EDiamondType EliminateType, const shared_ptr<MDGameState>& GameState)
{
    if (!GameState)
    {
        return 0;
    }

    if (EliminateType != EntryDiamond->DiamondType)
    {
        return 0;
    }

    const int ResultCount = GameState->GetEliminatedDiamondSet().count(EntryDiamond.get());
    if (ResultCount > 0)
    {
        return 0;
    }

    GameState->GetEliminatedDiamondSet().insert(EntryDiamond.get());

    // All eliminated diamonds need to check their neighborhood and do the same thing
    return 1 + CheckNeighborhood(EntryDiamond, EliminateType, GameState, EMoveDirection::UP)
        + CheckNeighborhood(EntryDiamond, EliminateType, GameState, EMoveDirection::RIGHT)
        + CheckNeighborhood(EntryDiamond, EliminateType, GameState, EMoveDirection::DOWN)
        + CheckNeighborhood(EntryDiamond, EliminateType, GameState, EMoveDirection::LEFT);
}

int MDDiamondUtilities::CheckNeighborhood(const shared_ptr<MDDiamond>& EntryDiamond, EDiamondType EliminateType,
    const shared_ptr<MDGameState>& GameState, EMoveDirection CheckDirection)
{
    const shared_ptr<MDDiamond> SideDiamond = dynamic_pointer_cast<MDDiamond>(EntryDiamond->GetSideActor(CheckDirection));

    if (SideDiamond)
    {
        return FindAllEliminatedDiamond(SideDiamond, EliminateType, GameState);
    }

    return 0;
}

void MDDiamondUtilities::EliminateDiamondsFromRecordSet(unordered_set<MDDiamond*>& RecordSet)
{
    MDScene* Scene = MDScene::Get();
    for (MDDiamond* Diamond : RecordSet)
    {
        if (Scene->CheckRegister(Diamond))
        {
            shared_ptr<MDActor> Actor = Scene->GetActorByPosition(Diamond->SceneComponent->GetVector());
            Scene->UnRegisterActor(Actor);
        }
    }
}

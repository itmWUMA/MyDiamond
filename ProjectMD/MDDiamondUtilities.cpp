#include "MDDiamondUtilities.h"
#include <queue>
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
        vector<Vector2D> EliminatePositions = EliminateDiamondsFromRecordSet(GameState->GetEliminatedDiamondSet());

        // update player's score
        const shared_ptr<MDPlayerState> PlayerState = GameMode->GetPlayerState();
        if (PlayerState)
        {
            PlayerState->Score += static_cast<float>(Count) * EntryDiamondScore;
        }
    }

    GameState->GetEliminatedDiamondSet().clear();

    FixSuspendingDiamonds();
}

bool MDDiamondUtilities::GenerateRowOfRandomDiamonds(const json11::Json& DiamondTemplates)
{
    MDScene* Scene = MDScene::Get();
    const shared_ptr<MDGameState> GameState = GameInstance->GetGameMode()->GetGameState();
    if (!GameState)
    {
        return false;
    }

    // all diamonds move down to the row below
    const unordered_set<shared_ptr<MDActor>> ActorSet = Scene->GetActorSet();
    for (const shared_ptr<MDActor>& Actor : ActorSet)
    {
        shared_ptr<MDDiamond> Diamond = dynamic_pointer_cast<MDDiamond>(Actor);
        if (Diamond)
        {
            Diamond->Move(EMoveDirection::DOWN, 1);

            if (Diamond->IsMeetingDeadLine())
            {
                GameState->SetGameOver();
                return false;
            }
        }
    }

    const int Col = Scene->GetCol();
    const size_t DiamondTemplatesCount = DiamondTemplates.array_items().size();
    for (int i = 0; i < Col; ++i)
    {
        const json11::Json& DiamondTemplate = DiamondTemplates[rand() % DiamondTemplatesCount];
        shared_ptr<MDDiamond> Diamond = make_shared<MDDiamond>(DiamondTemplate);
        Diamond->SceneComponent->SetVector(Vector2D(0, i));
        Scene->RegisterActor(Diamond);
    }

    return true;
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

vector<Vector2D> MDDiamondUtilities::EliminateDiamondsFromRecordSet(unordered_set<MDDiamond*>& RecordSet)
{
    MDScene* Scene = MDScene::Get();
    vector<Vector2D> EliminatePositions;
    for (const MDDiamond* Diamond : RecordSet)
    {
        if (Scene->CheckRegister(Diamond))
        {
            shared_ptr<MDActor> Actor = Scene->GetActorByPosition(Diamond->SceneComponent->GetVector());
            EliminatePositions.push_back(Actor->SceneComponent->GetVector());
            Scene->UnRegisterActor(Actor);
        }
    }
    return EliminatePositions;
}

int MDDiamondUtilities::CheckDiamondSuspend(const shared_ptr<MDDiamond>& Diamond)
{
    const MDScene* Scene = MDScene::Get();
    if (!Scene->CheckActorPosition(Diamond))
    {
        return 0;
    }

    const int DiamondX = Diamond->SceneComponent->GetX();
    const int DiamondY = Diamond->SceneComponent->GetY();
    int CurX = DiamondX - 1;
    for (; CurX >= 0; --CurX)
    {
        if (Scene->GetActorByPosition(Vector2D(CurX, DiamondY)))
        {
            break;
        }
    }

    return DiamondX - CurX - 1;
}

void MDDiamondUtilities::FixSuspendingDiamonds()
{
    MDScene* Scene = MDScene::Get();
    const unordered_set<shared_ptr<MDActor>>& ActorSet = Scene->GetActorSet();
    priority_queue<shared_ptr<MDDiamond>, vector<shared_ptr<MDDiamond>>, MDDiamondCompairHandler_SmallX> DiamondHeap;

    // sort diamonds, the upper diamond in the scene need to be checked preferentially
    for (const shared_ptr<MDActor>& Actor : ActorSet)
    {
        shared_ptr<MDDiamond> Diamond = dynamic_pointer_cast<MDDiamond>(Actor);
        if (Diamond)
        {
            DiamondHeap.push(Diamond);
        }
    }

    while (!DiamondHeap.empty())
    {
        shared_ptr<MDDiamond> Diamond = DiamondHeap.top();
        const int MoveDistance = CheckDiamondSuspend(Diamond);
        if (MoveDistance > 0)
        {
            Diamond->Move(EMoveDirection::UP, MoveDistance);
        }
        DiamondHeap.pop();
    }

    Scene->UpdateSlots();
}

bool MDDiamondCompairHandler_SmallX::operator()(const shared_ptr<MDDiamond>& A, const shared_ptr<MDDiamond>& B) const
{
    return A->SceneComponent->GetX() > B->SceneComponent->GetX();
}

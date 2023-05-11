#include "MDScene.h"
#include <iostream>
#include "Windows.h"
#include "MDActor.h"
#include "MDDebugger.h"
#include "MDSceneComponent.h"
using namespace std;

MDScene* MDScene::SceneInstance = nullptr;

MDScene::MDScene()
{
    Slots = Map(SizeX, vector<shared_ptr<MDActor>>(SizeY, nullptr));
}

void MDScene::ClearSlots()
{
    for (vector<shared_ptr<MDActor>>& Row : Slots)
    {
        for (shared_ptr<MDActor>& SlotElem : Row)
        {
            SlotElem = nullptr;
        }
    }
}

shared_ptr<MDActor>& MDScene::GetSlotByActor_Unchecked(const shared_ptr<MDActor>& Actor)
{
    const int PosX = Actor->SceneComponent->GetX();
    const int PosY = Actor->SceneComponent->GetY();
    return Slots[PosX][PosY];
}

void MDScene::NullRender()
{
    cout << ' ';
}

void MDScene::RenderNewLine()
{
    cout << '\n';
}

MDScene* MDScene::Get()
{
    if (!SceneInstance)
    {
        SceneInstance = new MDScene;
    }

    return SceneInstance;
}

MDScene::~MDScene()
{
#if _DEBUG
    MDDebugger::Log(DEBUG_FUNC_SIGN);
#endif 
}

shared_ptr<MDActor> MDScene::GetActorByPosition(const Vector2D& Position) const
{
    if (!CheckActorPosition(Position))
    {
        return nullptr;
    }

    return Slots[Position.first][Position.second];
}

bool MDScene::CheckActorPosition(const Vector2D& ActorPosition) const
{
    const int PosX = ActorPosition.first;
    const int PosY = ActorPosition.second;
    return (PosX >= 0 && PosX < SizeX && PosY >= 0 && PosY < SizeY);
}

bool MDScene::CheckActorPosition(const shared_ptr<MDActor>& Actor) const
{
    return CheckActorPosition(Actor->SceneComponent->GetVector());
}

void MDScene::RegisterActor(const shared_ptr<MDActor>& Actor)
{
    if (!CheckActorPosition(Actor))
    {
        return;
    }

    ActorSet.insert(Actor);
    GetSlotByActor_Unchecked(Actor) = Actor;
}

void MDScene::UnRegisterActor(const shared_ptr<MDActor>& Actor)
{
    const auto ActorIter = ActorSet.find(Actor);
    if (ActorIter != ActorSet.end())
    {
        GetSlotByActor_Unchecked(*ActorIter) = nullptr;
        ActorSet.erase(ActorIter);
    }
}

bool MDScene::CheckRegister(const MDActor* ActorPtr) const
{
    auto Result = find_if(ActorSet.begin(), ActorSet.end(),
        [ActorPtr](const std::shared_ptr<MDActor>& Elem) -> bool
        {
            return Elem.get() == ActorPtr;
        });
    return (*Result) != nullptr;
}

void MDScene::UpdateSlots()
{
    ClearSlots();
    for (const shared_ptr<MDActor>& Actor : ActorSet)
    {
        GetSlotByActor_Unchecked(Actor) = Actor;
    }
}

void MDScene::RenderSence() const
{
    for (const vector<shared_ptr<MDActor>>& Row : Slots)
    {
        for (const shared_ptr<MDActor>& SlotElem : Row)
        {
            if (SlotElem)
            {
                SlotElem->Render();
            }
            else
            {
                NullRender();
            }
        }
        RenderNewLine();
    }
}

void MDScene::ChangeGameMode(const shared_ptr<MDGameMode>& NewGameMode)
{
    CurrentGameMode = NewGameMode;
}

shared_ptr<MDGameMode> MDScene::GetGameMode() const
{
    return CurrentGameMode;
}

void MDScene::DeleteScene()
{
    delete SceneInstance;
    SceneInstance = nullptr;
}

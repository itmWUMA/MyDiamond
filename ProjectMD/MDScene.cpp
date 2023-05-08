#include "MDScene.h"
#include <iostream>
#include "MDActor.h"
#include "MDSceneComponent.h"
using namespace std;

MDScene* MDScene::SceneInstance = new MDScene();

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
    if (*ActorIter)
    {
        GetSlotByActor_Unchecked(*ActorIter) = nullptr;
        ActorSet.erase(ActorIter);
    }
}

bool MDScene::CheckRegister(const shared_ptr<MDActor>& Actor) const
{
    return *(ActorSet.find(Actor)) != nullptr;
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
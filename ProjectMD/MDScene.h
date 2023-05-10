#pragma once

#include <vector>
#include <memory>
#include <unordered_set>
#include "MDDefines.h"
using namespace std;

class MDActor;
class MDGameMode;

/* A singleton scene which contains actors */
class MDScene
{
public:
    typedef vector<vector<shared_ptr<MDActor>>> Map;

public:
    static MDScene* Get() { return SceneInstance; }

public:
    ~MDScene();
    inline int GetRow() const { return SizeX; }
    inline int GetCol() const { return SizeY; }
    shared_ptr<MDActor> GetActorByPosition(const Vector2D& ActorPosition) const;
    bool CheckActorPosition(const Vector2D& ActorPosition) const;
    bool CheckActorPosition(const shared_ptr<MDActor>& Actor) const;
    void RegisterActor(const shared_ptr<MDActor>& Actor);
    void UnRegisterActor(const shared_ptr<MDActor>& Actor);
    bool CheckRegister(const MDActor* ActorPtr) const;
    void UpdateSlots();
    void RenderSence() const;
    void ChangeGameMode(const shared_ptr<MDGameMode>& NewGameMode);
    shared_ptr<MDGameMode> GetGameMode() const;

private:
    MDScene();
    MDScene(const MDScene& Scene) = delete;
    MDScene& operator=(const MDScene& Scene) = delete;
    void ClearSlots();
    shared_ptr<MDActor>& GetSlotByActor_Unchecked(const shared_ptr<MDActor>& Actor);
    static void NullRender();
    static void RenderNewLine();

private:
    static MDScene* SceneInstance;

private:
    int SizeX = 10;
    int SizeY = 5;

    /* Each slot can contain an actor */
    Map Slots;

    /* A list recording all actors which have been registered */
    unordered_set<shared_ptr<MDActor>> ActorSet;

    shared_ptr<MDGameMode> CurrentGameMode = nullptr;
};
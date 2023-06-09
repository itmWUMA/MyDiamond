#pragma once

#include <memory>
#include "MDDefines.h"
using namespace std;

class MDPawn;
class MDPlayerState;
class MDInputComponent;

class MDPlayerController : enable_shared_from_this<MDPlayerController>
{
public:
    MDPlayerController();
    MDPlayerController(const shared_ptr<MDPlayerState>& PlayerState);

    void InitPlayerController(const shared_ptr<MDPlayerState>& PlayerState);
    void Possess(const shared_ptr<MDPawn>& PossessedPawn);
    void UnPossess();
    void OnPawnMove(EMoveDirection Direction) const;
    void OnInteract() const;
    shared_ptr<MDInputComponent> GetInputComponent() const;

private:
    shared_ptr<MDInputComponent> InputComponent;
    shared_ptr<MDPlayerState> PlayerState;
    shared_ptr<MDPawn> PossessedPawn;
};


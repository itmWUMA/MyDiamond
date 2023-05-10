#pragma once

#include <memory>
#include "MDDefines.h"
using namespace std;

class MDPlayerState;
class MDInputComponent;

class MDPlayerController : enable_shared_from_this<MDPlayerController>
{
public:
    MDPlayerController();
    MDPlayerController(const shared_ptr<MDPlayerState>& PlayerState);

    void InitPlayerController(const shared_ptr<MDPlayerState>& PlayerState);
    void OnPawnMove(EMoveDirection Direction) const;

private:
    shared_ptr<MDPlayerState> PlayerState;
    shared_ptr<MDInputComponent> InputComponent;
};


#include "MDPlayerController.h"

MDPlayerController::MDPlayerController(const shared_ptr<::MDPlayerState>& PlayerState)
    :PlayerState(PlayerState)
{
}

void MDPlayerController::InitPlayerController(const shared_ptr<MDPlayerState>& PlayerState)
{
    this->PlayerState = PlayerState;
}

#include "MDPawn.h"
#include "MDPlayerState.h"

MDPawn::MDPawn(const shared_ptr<::MDPlayerState>& PlayerState)
    : PlayerState(PlayerState)
{
}

void MDPawn::InitPawn(const shared_ptr<::MDPlayerState>& PlayerState)
{
    this->PlayerState = PlayerState;
}

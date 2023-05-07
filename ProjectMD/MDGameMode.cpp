#include "MDGameMode.h"
#include "MDPawn.h"
#include "MDPlayerController.h"

MDGameMode::MDGameMode(const shared_ptr<MDPawn>& DefaultPawn, 
    const shared_ptr<MDPlayerController>& PlayerController,
    const shared_ptr<MDPlayerState>& PlayerState)
    : DefaultPawn(DefaultPawn), PlayerController(PlayerController), PlayerState(PlayerState)
{
    this->DefaultPawn->InitPawn(this->PlayerState);
    this->PlayerController->InitPlayerController(this->PlayerState);
}

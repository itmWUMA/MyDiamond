#include "InputCommand.h"

#include "MDPlayerController.h"
#include "MDGameInstance.h"

MDMoveCommand::MDMoveCommand(EMoveDirection Direction)
    :Direction(Direction)
{
}

void MDMoveCommand::Execute(const shared_ptr<MDPlayerController>& PlayerController)
{
    PlayerController->OnPawnMove(Direction);
}

void MDQuitGameCommand::Execute(const shared_ptr<MDPlayerController>& PlayerController)
{
    GameInstance->QuitGame();
}

void MDInteractCommand::Execute(const shared_ptr<MDPlayerController>& PlayerController)
{
    PlayerController->OnInteract();
}

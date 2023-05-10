#include "InputCommand.h"

#include "MDPlayerController.h"

MDMoveCommand::MDMoveCommand(EMoveDirection Direction)
    :Direction(Direction)
{
}

void MDMoveCommand::Execute(const shared_ptr<MDPlayerController>& PlayerController)
{
    PlayerController->OnPawnMove(Direction);
}

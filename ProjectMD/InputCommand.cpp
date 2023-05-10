#include "InputCommand.h"

#include "MDPlayerController.h"

MDMoveCommand::MDMoveCommand(const weak_ptr<MDPlayerController>& PlayerControllerCahce, EMoveDirection Direction)
    :Direction(Direction)
{
    this->PlayerControllerCache = PlayerControllerCahce;
}

void MDMoveCommand::Execute()
{
    if (!PlayerControllerCache.expired())
    {
        PlayerControllerCache.lock()->OnPawnMove(Direction);
    }
}

#include "MDPlayerController.h"
#include "MDInputComponent.h"
#include "MDPawn.h"

MDPlayerController::MDPlayerController()
{
    InputComponent = make_shared<MDInputComponent>(weak_from_this());
}

MDPlayerController::MDPlayerController(const shared_ptr<::MDPlayerState>& PlayerState)
    : MDPlayerController()
{
    this->PlayerState = PlayerState;
}

void MDPlayerController::InitPlayerController(const shared_ptr<MDPlayerState>& PlayerState)
{
    this->PlayerState = PlayerState;
}

void MDPlayerController::Possess(const shared_ptr<MDPawn>& PossessedPawn)
{
    this->PossessedPawn = PossessedPawn;
}

void MDPlayerController::UnPossess()
{
    this->PossessedPawn = nullptr;
}

void MDPlayerController::OnPawnMove(EMoveDirection Direction) const
{
    if (!PossessedPawn)
    {
        return;
    }

    PossessedPawn->Move(Direction);
}

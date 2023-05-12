#include "MDPlayerController.h"
#include "MDInputComponent.h"
#include "MDPawn.h"
#include "MDPlayerState.h"

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
    if (!PossessedPawn || Direction == EMoveDirection::UP || Direction == EMoveDirection::DOWN)
    {
        return;
    }

    PossessedPawn->Move(Direction);
    ++PlayerState->PlayerStepCount;
}

void MDPlayerController::OnInteract() const
{
    if (!PossessedPawn)
    {
        return;
    }

    PlayerState->AcquiredDiamond ? PossessedPawn->Throw() : PossessedPawn->Grab();
}

shared_ptr<MDInputComponent> MDPlayerController::GetInputComponent() const
{
    return InputComponent;
}

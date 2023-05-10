#include "MDPlayerController.h"
#include "MDInputComponent.h"

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

void MDPlayerController::OnPawnMove(EMoveDirection Direction) const
{

}

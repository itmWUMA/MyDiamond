#include "MDGameMode.h"
#include "MDPawn.h"
#include "MDPlayerController.h"
#include "MDUserWidget.h"

MDGameMode::MDGameMode(const shared_ptr<MDPawn>& DefaultPawn,
    const shared_ptr<MDPlayerController>& PlayerController,
    const shared_ptr<MDPlayerState>& PlayerState,
    const shared_ptr<MDGameState>& GameState,
    const shared_ptr<MDUserWidget>& HUD)
    : DefaultPawn(DefaultPawn),
    PlayerController(PlayerController),
    PlayerState(PlayerState),
    GameState(GameState),
    HUD(HUD)
{
    this->DefaultPawn->InitPawn(this->PlayerState);
    this->PlayerController->InitPlayerController(this->PlayerState);
    this->PlayerController->Possess(this->DefaultPawn);
    this->HUD->InitUserWidget(PlayerState, GameState);
}

shared_ptr<MDPawn> MDGameMode::GetDefaultPawn() const
{
    return DefaultPawn;
}

shared_ptr<MDPlayerController> MDGameMode::GetPlayerController() const
{
    return PlayerController;
}

shared_ptr<MDPlayerState> MDGameMode::GetPlayerState() const
{
    return PlayerState;
}

shared_ptr<MDGameState> MDGameMode::GetGameState() const
{
    return GameState;
}

shared_ptr<MDUserWidget> MDGameMode::GetHUD() const
{
    return HUD;
}

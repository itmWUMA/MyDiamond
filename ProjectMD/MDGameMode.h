#pragma once

#include <memory>
using namespace std;

class MDPawn;
class MDPlayerController;
class MDPlayerState;
class MDGameState;
class MDUserWidget;

class MDGameMode
{
public:
    MDGameMode(const shared_ptr<MDPawn>& DefaultPawn,
        const shared_ptr<MDPlayerController>& PlayerController,
        const shared_ptr<MDPlayerState>& PlayerState,
        const shared_ptr<MDGameState>& GameState,
        const shared_ptr<MDUserWidget>& HUD);

    shared_ptr<MDPawn> GetDefaultPawn() const;
    shared_ptr<MDPlayerController> GetPlayerController() const;
    shared_ptr<MDPlayerState> GetPlayerState() const;
    shared_ptr<MDGameState> GetGameState() const;
    shared_ptr<MDUserWidget> GetHUD() const;

private:
    shared_ptr<MDPawn> DefaultPawn;
    shared_ptr<MDPlayerController> PlayerController;
    shared_ptr<MDPlayerState> PlayerState;
    shared_ptr<MDGameState> GameState;
    shared_ptr<MDUserWidget> HUD;
};


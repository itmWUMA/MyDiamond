#include "MDGameMode.h"
#include "MDPawn.h"
#include "MDPlayerController.h"
#include "MDPlayerState.h"

shared_ptr<MDGameMode> InitGameMode()
{
    shared_ptr<MDPawn> DefaultPawn = make_shared<MDPawn>();
    shared_ptr<MDPlayerController> PlayerController = make_shared<MDPlayerController>();
    shared_ptr<MDPlayerState> PlayerState = make_shared<MDPlayerState>();
    shared_ptr<MDGameMode> GameModeInstance = make_shared<MDGameMode>(DefaultPawn, PlayerController, PlayerState);
    return GameModeInstance;
}

int main(int argc, char* argv[])
{
    shared_ptr<MDGameMode> GameModeInstance = InitGameMode();

    return 0;
}

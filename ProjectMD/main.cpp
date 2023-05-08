#include "MDDiamond.h"
#include "MDGameMode.h"
#include "MDPawn.h"
#include "MDPlayerController.h"
#include "MDPlayerState.h"
#include "MDScene.h"

shared_ptr<MDGameMode> InitGameMode()
{
    shared_ptr<MDPawn> DefaultPawn = make_shared<MDPawn>();
    shared_ptr<MDPlayerController> PlayerController = make_shared<MDPlayerController>();
    shared_ptr<MDPlayerState> PlayerState = make_shared<MDPlayerState>();
    shared_ptr<MDGameMode> GameModeInstance = make_shared<MDGameMode>(DefaultPawn, PlayerController, PlayerState);
    return GameModeInstance;
}

#if _DEBUG
void DebugTest()
{
    shared_ptr<MDGameMode> GameModeInstance = InitGameMode();
    shared_ptr<MDDiamond> Diamond = make_shared<MDDiamond>('+', EDiamondType::TYPE_ONE);
    MDScene::Get()->RegisterActor(Diamond);
    Diamond->Move(EMoveDirection::RIGHT);
    Diamond->Move(EMoveDirection::DOWN);
    MDScene::Get()->UpdateSlots();
    MDScene::Get()->RenderSence();
}
#endif

int main(int argc, char* argv[])
{
#if _DEBUG
    DebugTest();
#endif

    return 0;
}

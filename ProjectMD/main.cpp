#include "MDDiamond.h"
#include "MDGameMode.h"
#include "MDGameState.h"
#include "MDPawn.h"
#include "MDPlayerController.h"
#include "MDPlayerState.h"
#include "MDScene.h"

shared_ptr<MDGameMode> InitGameMode()
{
    shared_ptr<MDPawn> DefaultPawn = make_shared<MDPawn>();
    shared_ptr<MDPlayerController> PlayerController = make_shared<MDPlayerController>();
    shared_ptr<MDPlayerState> PlayerState = make_shared<MDPlayerState>();
    shared_ptr<MDGameState> GameState = make_shared<MDGameState>();
    shared_ptr<MDGameMode> GameModeInstance = make_shared<MDGameMode>(DefaultPawn, PlayerController, PlayerState, GameState);
    MDScene::Get()->ChangeGameMode(GameModeInstance);
    return GameModeInstance;
}

#if _DEBUG
void DebugTest()
{
    shared_ptr<MDGameMode> GameModeInstance = InitGameMode();

    shared_ptr<MDDiamond> Diamond1 = make_shared<MDDiamond>('+', EDiamondType::TYPE_ONE);
    MDScene::Get()->RegisterActor(Diamond1);
    Diamond1->MoveToPosition(Vector2D(0, 1));
    shared_ptr<MDDiamond> Diamond2 = make_shared<MDDiamond>('+', EDiamondType::TYPE_ONE);
    MDScene::Get()->RegisterActor(Diamond2);
    Diamond2->MoveToPosition(Vector2D(1, 0));
    shared_ptr<MDDiamond> Diamond3 = make_shared<MDDiamond>('+', EDiamondType::TYPE_ONE);
    MDScene::Get()->RegisterActor(Diamond3);
    Diamond3->MoveToPosition(Vector2D(1, 1));
    shared_ptr<MDDiamond> Diamond4 = make_shared<MDDiamond>('+', EDiamondType::TYPE_ONE);
    MDScene::Get()->RegisterActor(Diamond4);
    Diamond4->MoveToPosition(Vector2D(1, 2));
    shared_ptr<MDDiamond> Diamond5 = make_shared<MDDiamond>('+', EDiamondType::TYPE_ONE);
    MDScene::Get()->RegisterActor(Diamond5);
    Diamond5->MoveToPosition(Vector2D(2, 1));
    shared_ptr<MDDiamond> Diamond6 = make_shared<MDDiamond>('+', EDiamondType::TYPE_ONE);
    MDScene::Get()->RegisterActor(Diamond6);
    Diamond6->MoveToPosition(Vector2D(3, 1));
    shared_ptr<MDDiamond> Diamond7 = make_shared<MDDiamond>('*', EDiamondType::TYPE_ONE);
    MDScene::Get()->RegisterActor(Diamond7);
    Diamond7->MoveToPosition(Vector2D(0, 4));

    Diamond6->Eliminate(EDiamondType::TYPE_ONE);

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

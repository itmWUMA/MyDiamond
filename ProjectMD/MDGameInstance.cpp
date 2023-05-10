#include "MDGameInstance.h"

#include "InputCommand.h"
#include "MDDefines.h"
#include "MDDiamond.h"
#include "MDGameState.h"
#include "MDInputComponent.h"
#include "MDPawn.h"
#include "MDPlayerController.h"
#include "MDPlayerState.h"
#include "MDScene.h"

MDGameInstance::MDGameInstance()
{
    CreateGameMode();
    InitScene();
    Play();
}

void MDGameInstance::CreateGameMode()
{
    shared_ptr<MDPawn> DefaultPawn = make_shared<MDPawn>('@');
    shared_ptr<MDPlayerController> PlayerController = make_shared<MDPlayerController>();
    shared_ptr<MDPlayerState> PlayerState = make_shared<MDPlayerState>(Vector2D(9, 2));
    shared_ptr<MDGameState> GameState = make_shared<MDGameState>();
    GameMode = make_shared<MDGameMode>(DefaultPawn, PlayerController, PlayerState, GameState);
    MDScene::Get()->ChangeGameMode(GameMode);
}

void MDGameInstance::InitScene()
{
#if _DEBUG
    shared_ptr<MDDiamond> Diamond1 = make_shared<MDDiamond>('+', EDiamondType::TYPE_ONE);
    MDScene::Get()->RegisterActor(Diamond1);
    Diamond1->MoveToPosition(Vector2D(0, 1));
    shared_ptr<MDDiamond> Diamond2 = make_shared<MDDiamond>('+', EDiamondType::TYPE_ONE);
    MDScene::Get()->RegisterActor(Diamond2);
    Diamond2->MoveToPosition(Vector2D(1, 0));
    shared_ptr<MDDiamond> Diamond3 = make_shared<MDDiamond>('*', EDiamondType::TYPE_FIVE);
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
#endif
}

void MDGameInstance::Play()
{
#if _DEBUG
    MDScene::Get()->RenderSence();
    while (true)
    {
        auto command = GameMode->GetPlayerController()->InputComponent->HandleInput();
        command->Execute(GameMode->GetPlayerController());
        MDScene::Get()->RenderSence();
    }
#endif
}
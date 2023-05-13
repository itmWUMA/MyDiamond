#include "MDGameInstance.h"

#include <conio.h>
#include <fstream>
#include <iostream>
#include <thread>
#include "InputCommand.h"
#include "MDDebugger.h"
#include "MDDefines.h"
#include "MDDiamond.h"
#include "MDGameState.h"
#include "MDInputComponent.h"
#include "MDPawn.h"
#include "MDPlayerController.h"
#include "MDPlayerState.h"
#include "MDScene.h"
#include "MDUserWidget.h"

unique_ptr<MDGameInstance> GameInstance;

MDGameInstance::MDGameInstance()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    if (LoadConfig())
    {
        CreateGameMode();
    }
}

MDGameInstance::~MDGameInstance()
{
#if _DEBUG
    MDDebugger::Log(DEBUG_FUNC_SIGN);
#endif
}

void MDGameInstance::CreateGameMode()
{
    shared_ptr<MDPawn> DefaultPawn = make_shared<MDPawn>(ConfigJson["PawnTemplate"]);

    shared_ptr<MDPlayerController> PlayerController = make_shared<MDPlayerController>();

    shared_ptr<MDPlayerState> PlayerState = make_shared<MDPlayerState>(ConfigJson["PawnTemplate"]);

    shared_ptr<MDGameState> GameState = make_shared<MDGameState>(ConfigJson["DeadLine"]);

    GameMode = make_shared<MDGameMode>(DefaultPawn, PlayerController, PlayerState, GameState);
    MDScene::Get()->ChangeGameMode(GameMode);
}

void MDGameInstance::OnEndPlay()
{
    CurrentUI = make_shared<MDPlayEndUI>();
    CurrentUI->Render();
    MDScene::DeleteScene();
}

bool MDGameInstance::LoadConfig()
{
    ifstream InputFileStream(CONFIG_PATH, ios::in);
    if (!InputFileStream.is_open())
    {
        return false;
    }

    string JsonStr;
    char Buffer[1024] = { 0 };
    while (InputFileStream >> Buffer)
    {
        JsonStr.append(Buffer);
    }

    InputFileStream.close();

    string ErrorCode;
    ConfigJson = json11::Json::parse(JsonStr, ErrorCode);

    return ErrorCode.empty();
}

void MDGameInstance::Delay(int Millisecond)
{
    this_thread::sleep_for(chrono::milliseconds(Millisecond));
    // clear input buffer
    while (_kbhit())
    {
        _getch();
    }
}

void MDGameInstance::OnEnterNextTurn() const
{
    if (ConfigJson["DiamondTemplates"].is_array())
    {
        MDDiamondUtilities::GenerateRowOfRandomDiamonds(ConfigJson["DiamondTemplates"]);
    }
}

void MDGameInstance::OnGameOver()
{
    CurrentUI = make_shared<MDGameOverUI>();
    CurrentUI->Render();
    QuitGame();
}

void MDGameInstance::OnGameStart()
{
    OnEnterNextTurn();
    CurrentUI = make_shared<MDMainUI>(GameMode->GetPlayerState(), GameMode->GetGameState());
}

void MDGameInstance::OnBeginPlay()
{
    // TODO: game entry
}

void MDGameInstance::OnUpdata()
{
    if (CurrentUI)
    {
        CurrentUI->Render();
    }

    shared_ptr<IInputCommand> Command = GameMode->GetPlayerController()->GetInputComponent()->HandleInput();
    if (Command)
    {
        Command->Execute(GameMode->GetPlayerController());
    }

    if (GameMode->GetGameState() && GameMode->GetGameState()->IsGameOver())
    {
        OnGameOver();
    }

    if (bQuitGame)
    {
        OnEndPlay();
    }
}

void MDGameInstance::Play()
{
    OnBeginPlay();

    OnGameStart();

    while (!bQuitGame)
    {
        OnUpdata();
    }
}

void MDGameInstance::QuitGame()
{
    bQuitGame = true;
}

void MDGameInstance::IncreaseTurn() const
{
    const shared_ptr<MDGameState> GameState = GameMode->GetGameState();
    if (GameState && GameState->IsGameOver())
    {
        return;
    }

    if (GameState)
    {
        GameState->IncreaseTurnCount();
    }

    if (CurrentUI)
    {
        CurrentUI->Render();
    }
    
    Delay(500);

    OnEnterNextTurn();
}

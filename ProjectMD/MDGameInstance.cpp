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
        InitScene();
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
    const json11::Json PawnConfig = ConfigJson["PawnTemplate"];
    shared_ptr<MDPawn> DefaultPawn = PawnConfig["Texture"].is_string() ?
        make_shared<MDPawn>(PawnConfig["Texture"].string_value().at(0)) : make_shared<MDPawn>();

    shared_ptr<MDPlayerController> PlayerController = make_shared<MDPlayerController>();

    shared_ptr<MDPlayerState> PlayerState;
    if (PawnConfig["DefaultPosition"].is_array())
    {
        int X = PawnConfig["DefaultPosition"].array_items()[0].int_value();
        int Y = PawnConfig["DefaultPosition"].array_items()[1].int_value();
        PlayerState = make_shared<MDPlayerState>(Vector2D(X, Y));
    }
    else
    {
        PlayerState = make_shared<MDPlayerState>();
    }

    shared_ptr<MDGameState> GameState = make_shared<MDGameState>();

    shared_ptr<MDUserWidget> HUD = make_shared<MDUserWidget>();

    GameMode = make_shared<MDGameMode>(DefaultPawn, PlayerController, PlayerState, GameState, HUD);
    MDScene::Get()->ChangeGameMode(GameMode);
}

void MDGameInstance::InitScene()
{
    OnEnterNextTurn();
}

void MDGameInstance::OnEndGame() const
{
    GameMode->GetHUD()->RenderQuitUI();
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

void MDGameInstance::Play()
{
    do
    {
        GameMode->GetHUD()->Render();

        shared_ptr<IInputCommand> Command = GameMode->GetPlayerController()->GetInputComponent()->HandleInput();
        if (Command)
        {
            Command->Execute(GameMode->GetPlayerController());
        }

        if (bQuitGame)
        {
            OnEndGame();
        }
    } while (!bQuitGame);
}

void MDGameInstance::QuitGame()
{
    bQuitGame = true;
}

void MDGameInstance::IncreaseTurn() const
{
    const shared_ptr<MDGameState> GameState = GameMode->GetGameState();
    if (GameState)
    {
        GameState->IncreaseTurnCount();
    }

    GameMode->GetHUD()->Render();
    Delay(500);

    OnEnterNextTurn();
}

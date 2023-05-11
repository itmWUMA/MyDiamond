#pragma once

#include <memory>
#include "MDGameMode.h"
using namespace std;

class MDGameInstance
{
public:
    MDGameInstance();
    void Play();
    void QuitGame();

private:
    void CreateGameMode();
    void InitScene();

private:
    shared_ptr<MDGameMode> GameMode;
    bool bQuitGame = false;
};

extern MDGameInstance* GameInstance;
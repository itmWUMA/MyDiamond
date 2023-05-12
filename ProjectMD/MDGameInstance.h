#pragma once

#include <memory>
#include "json11/json11.hpp"
#include "MDGameMode.h"
using namespace std;

class MDGameInstance
{
public:
    MDGameInstance();
    virtual ~MDGameInstance();
    void Play();
    void QuitGame();
    void IncreaseTurn() const;

private:
    void CreateGameMode();
    void InitScene();
    void OnEndGame() const;
    bool LoadConfig();

private:
    shared_ptr<MDGameMode> GameMode;
    bool bQuitGame = false;
    json11::Json ConfigJson;
};

extern unique_ptr<MDGameInstance> GameInstance;
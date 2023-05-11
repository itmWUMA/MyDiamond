#pragma once

#include <memory>
#include "MDGameMode.h"
using namespace std;

class MDGameInstance
{
public:
    MDGameInstance();
    virtual ~MDGameInstance();
    void Play();
    void QuitGame();

private:
    void CreateGameMode();
    void InitScene();
    void OnEndGame() const;

private:
    shared_ptr<MDGameMode> GameMode;
    bool bQuitGame = false;
};

extern unique_ptr<MDGameInstance> GameInstance;
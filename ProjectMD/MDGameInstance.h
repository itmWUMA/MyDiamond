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

protected:
    virtual void OnEndGame() const;
    virtual void OnEnterNextTurn() const;

private:
    void CreateGameMode();
    void InitScene();
    bool LoadConfig();
    static void Delay(int Millisecond);

private:
    shared_ptr<MDGameMode> GameMode;
    bool bQuitGame = false;
    json11::Json ConfigJson;
};

extern unique_ptr<MDGameInstance> GameInstance;
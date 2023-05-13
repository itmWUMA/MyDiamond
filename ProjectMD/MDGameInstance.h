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
    inline shared_ptr<MDGameMode> GetGameMode() const { return GameMode; }

protected:
    virtual void OnEndGame() const;
    virtual void OnEnterNextTurn() const;
    virtual void OnGameOver();

private:
    void CreateGameMode();
    bool LoadConfig();
    static void Delay(int Millisecond);

private:
    shared_ptr<MDGameMode> GameMode;
    bool bQuitGame = false;
    json11::Json ConfigJson;
};

extern unique_ptr<MDGameInstance> GameInstance;
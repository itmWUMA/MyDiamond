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
    void RestartGame();
    void IncreaseTurn() const;
    inline shared_ptr<MDGameMode> GetGameMode() const { return GameMode; }
    inline bool IsRestartGame() const { return bRestartGame; }

protected:
    virtual void OnEndPlay();
    virtual void OnEnterNextTurn() const;
    virtual void OnGameOver();
    virtual void OnGameStart();
    virtual void OnBeginPlay();
    virtual void OnUpdata();

private:
    void CreateGameMode();
    bool LoadConfig();
    static void Delay(int Millisecond);

private:
    shared_ptr<MDGameMode> GameMode;
    shared_ptr<MDUserWidget> CurrentUI = nullptr;
    bool bQuitGame = false;
    bool bRestartGame = false;
    json11::Json ConfigJson;
};

extern unique_ptr<MDGameInstance> GameInstance;
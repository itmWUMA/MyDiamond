#pragma once

#include <memory>
#include "MDGameMode.h"
using namespace std;

class MDGameInstance
{
public:
    MDGameInstance();
    void Play();

private:
    void CreateGameMode();
    void InitScene();

private:
    shared_ptr<MDGameMode> GameMode;
};

extern unique_ptr<MDGameInstance> GameInstance;
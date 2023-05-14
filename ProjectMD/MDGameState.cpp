#include "MDGameState.h"
#include "MDDiamond.h"

MDGameState::MDGameState(const json11::Json& ConfigJson, float BestScore)
    : BestScore(BestScore)
{
    if (CheckConfig(ConfigJson))
    {
        DeadLine = ConfigJson.int_value();
    }
}

void MDGameState::SyncBestScore(float CurrentScore)
{
    if (CurrentScore > BestScore)
    {
        BestScore = CurrentScore;
    }
}

bool MDGameState::CheckConfig(const json11::Json& ConfigJson)
{
    return ConfigJson.is_number();
}

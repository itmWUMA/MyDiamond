#pragma once

#include <unordered_set>
#include "json11/json11.hpp"
using namespace std;

class MDDiamond;

class MDGameState
{
public:
    MDGameState(const json11::Json& ConfigJson);

    inline void IncreaseTurnCount() { ++TurnCount; }
    inline int GetTurnCount() const { return TurnCount; }
    inline unordered_set<MDDiamond*>& GetEliminatedDiamondSet() { return EliminatedDiamondSet; }
    inline int GetDeadLine() const { return DeadLine; }

private:
    static bool CheckConfig(const json11::Json& ConfigJson);

private:
    unordered_set<MDDiamond*> EliminatedDiamondSet;
    int TurnCount = 0;
    int DeadLine = 8;
};


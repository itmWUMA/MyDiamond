#pragma once

#include <unordered_set>
using namespace std;

class MDDiamond;

class MDGameState
{
public:
    MDGameState();

    inline void IncreaseTurnCount() { ++TurnCount; }
    inline int GetTurnCount() const { return TurnCount; }
    inline unordered_set<MDDiamond*>& GetEliminatedDiamondSet() { return EliminatedDiamondSet; }

private:
    unordered_set<MDDiamond*> EliminatedDiamondSet;
    int TurnCount = 0;
};


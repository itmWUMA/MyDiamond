#pragma once

#include <unordered_set>
using namespace std;

class MDDiamond;

class MDGameState
{
public:
    MDGameState();

public:
    unordered_set<MDDiamond*> EliminatedDiamondSet;
};


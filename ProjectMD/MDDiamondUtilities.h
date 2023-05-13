#pragma once

#include <memory>
#include <unordered_set>

#include "MDDefines.h"
using namespace std;

class MDDiamond;
class MDGameState;
enum class EDiamondType;
enum class EMoveDirection;

/* Offer some utility static methods to deal with functions about diamonds */
class MDDiamondUtilities
{
public:
    static void EliminateDiamonds(const shared_ptr<MDDiamond>& EntryDiamond, EDiamondType EliminateType);

private:
    static int FindAllEliminatedDiamond(const shared_ptr<MDDiamond>& EntryDiamond, EDiamondType EliminateType, const shared_ptr<MDGameState>& GameState);
    static int CheckNeighborhood(const shared_ptr<MDDiamond>& EntryDiamond, EDiamondType EliminateType, const shared_ptr<MDGameState>& GameState, EMoveDirection CheckDirection);
    static vector<Vector2D> EliminateDiamondsFromRecordSet(unordered_set<MDDiamond*>& RecordSet);
    static int CheckDiamondSuspend(const shared_ptr<MDDiamond>& Diamond);
    static void FixSuspendingDiamonds();
};

/* Diamond sort : smallest X as a heap */
class MDDiamondCompairHandler_SmallX
{
public:
    bool operator()(const shared_ptr<MDDiamond>& A, const shared_ptr<MDDiamond>& B) const;
};
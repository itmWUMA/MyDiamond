#pragma once

#include <memory>
#include <unordered_set>
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
    static void EliminateDiamondsFromRecordSet(unordered_set<MDDiamond*>& RecordSet);
};


#pragma once

#include <memory>
#include "MDActor.h"
#include "MDDefines.h"
using namespace std;

class MDRenderComponent;
class MDMovementComponent;
class MDGameState;
enum class EDiamondType;
enum class EMoveDirection;

class MDDiamond : public MDActor
{
public:
    MDDiamond(char Texture, EDiamondType DiamondType);
    virtual void Render() const override;
    void Move(EMoveDirection Direction);
    void MoveToPosition(Vector2D TargetPosition);
    /* Eliminate all suitable diamonds and return the count of eliminated diamonds */
    void Eliminate(EDiamondType EliminateType);

private:
    int FindAllEliminatedDiamond(EDiamondType EliminateType, const shared_ptr<MDGameState>& GameState);
    int CheckNeighborhood(EDiamondType EliminateType, const shared_ptr<MDGameState>& GameState, EMoveDirection CheckDirection) const;

public:
    char Texture;
    float Score = 1.f;
    const EDiamondType DiamondType;

private:
    shared_ptr<MDRenderComponent> RenderComponent;
    shared_ptr<MDMovementComponent> MovementComponent;
};
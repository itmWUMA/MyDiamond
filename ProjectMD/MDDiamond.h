#pragma once

#include <memory>
#include <unordered_set>
#include "MDActor.h"
#include "MDDefines.h"
#include "MDDiamondUtilities.h"
using namespace std;

class MDRenderComponent;
class MDMovementComponent;
class MDGameState;
enum class EDiamondType;
enum class EMoveDirection;

class MDDiamond : public MDActor
{
    friend MDDiamondUtilities;

public:
    MDDiamond();
    virtual ~MDDiamond() override;
    MDDiamond(char Texture, EDiamondType DiamondType);
    virtual void Render() const override;
    void Move(EMoveDirection Direction);
    void Move(EMoveDirection Direction, int Step);
    void MoveToPosition(Vector2D TargetPosition);
    bool IsMeetingDeadLine() const;

public:
    char Texture = '?';
    float Score = 1.f;
    const EDiamondType DiamondType = EDiamondType::TYPE_ONE;

private:
    shared_ptr<MDRenderComponent> RenderComponent;
    shared_ptr<MDMovementComponent> MovementComponent;
};
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
    MDDiamond(const json11::Json& ConfigJson);
    virtual ~MDDiamond() override;
    MDDiamond(char Texture, EDiamondType DiamondType);
    virtual void Render() const override;
    void Move(EMoveDirection Direction);
    void Move(EMoveDirection Direction, int Step);
    void MoveToPosition(Vector2D TargetPosition);
    bool IsMeetingDeadLine() const;
    inline float GetScore() const { return Score; }
    inline EDiamondType GetType() const { return DiamondType; }

private:
    static bool CheckConfig(const json11::Json& ConfigJson);

private:
    shared_ptr<MDRenderComponent> RenderComponent;
    shared_ptr<MDMovementComponent> MovementComponent;
    char Texture = '?';
    float Score = 1.f;
    EDiamondType DiamondType = EDiamondType::TYPE_ONE;
};
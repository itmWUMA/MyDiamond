#pragma once

#include <memory>
#include "MDActor.h"
using namespace std;

class MDRenderComponent;
class MDMovementComponent;
enum class EDiamondType;
enum class EMoveDirection;

class MDDiamond : public MDActor
{
public:
    MDDiamond(char Texture, EDiamondType DiamondType);
    virtual void Render() const override;
    void Move(EMoveDirection Direction);

private:

public:
    char Texture;
    float Score = 1.f;
    const EDiamondType DiamondType;

private:
    shared_ptr<MDRenderComponent> RenderComponent;
    shared_ptr<MDMovementComponent> MovementComponent;
};
#pragma once

#include <memory>
#include "MDActor.h"
using namespace std;

class MDRenderComponent;
enum class EDiamondType;

class MDDiamond : public MDActor
{
public:
    MDDiamond(char Texture, EDiamondType DiamondType);

public:
    char Texture;
    float Score = 1.f;
    const EDiamondType DiamondType;
    shared_ptr<MDRenderComponent> RenderComponent;
};
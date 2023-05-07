#include "MDDiamond.h"
#include "MDDefines.h"
#include "MDRenderComponent.h"

MDDiamond::MDDiamond(char Texture, EDiamondType DiamondType)
    : Texture(Texture), DiamondType(DiamondType)
{
    RenderComponent = make_shared<MDRenderComponent>();
}

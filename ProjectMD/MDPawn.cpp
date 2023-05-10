#include "MDPawn.h"
#include "MDDefines.h"
#include "MDDebugger.h"
#include "MDMovementComponent.h"
#include "MDPlayerState.h"
#include "MDRenderComponent.h"
#include "MDSceneComponent.h"

MDPawn::MDPawn(char Texture) : Texture(Texture), PlayerState(nullptr)
{
    RenderComponent = make_shared<MDRenderComponent>();
    MovementComponent = make_shared<MDMovementComponent>();
}

MDPawn::~MDPawn()
{
#if _DEBUG
    MDDebugger::Log(DEBUG_FUNC_SIGN);
#endif
}

MDPawn::MDPawn(char Texture, const shared_ptr<MDPlayerState>& PlayerState)
    : MDPawn(Texture)
{
    InitPawn(PlayerState);
}

void MDPawn::InitPawn(const shared_ptr<MDPlayerState>& PlayerStateIns)
{
    this->PlayerState = PlayerStateIns;
    if (PlayerState)
    {
        SceneComponent->SetVector(PlayerState->GetDefaultSpawnPosition());
    }
}

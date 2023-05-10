#pragma once

#include <memory>
#include "MDActor.h"
using namespace std;

class MDPlayerState;
class MDRenderComponent;
class MDMovementComponent;

class MDPawn : public MDActor, public enable_shared_from_this<MDPawn>
{
public:
    MDPawn(char Texture);
    virtual ~MDPawn() override;
    MDPawn(char Texture, const shared_ptr<MDPlayerState>& PlayerState);

    void InitPawn(const shared_ptr<MDPlayerState>& PlayerStateIns);
    void Move(EMoveDirection Direction);
    virtual void Render() const override;

private:
    char Texture;
    shared_ptr<MDPlayerState> PlayerState;
    shared_ptr<MDRenderComponent> RenderComponent;
    shared_ptr<MDMovementComponent> MovementComponent;
};
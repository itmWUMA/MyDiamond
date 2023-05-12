#pragma once

#include <memory>
#include "MDActor.h"
#include "MDDefines.h"
using namespace std;

class MDPlayerState;
class MDRenderComponent;
class MDMovementComponent;

class MDPawn : public MDActor, public enable_shared_from_this<MDPawn>
{
public:
    MDPawn();
    MDPawn(char Texture);
    virtual ~MDPawn() override;
    MDPawn(char Texture, const shared_ptr<MDPlayerState>& PlayerState);

    void InitPawn(const shared_ptr<MDPlayerState>& PlayerStateIns);
    void Move(EMoveDirection Direction) const;
    void Grab() const;
    void Throw() const;
    virtual void Render() const override;

private:
    /* Get the position of nearest actor which is above the pawn */
    bool GetUpperActorPosition(Vector2D& OutPosition) const;

private:
    char Texture = '!';
    shared_ptr<MDPlayerState> PlayerState;
    shared_ptr<MDRenderComponent> RenderComponent;
    shared_ptr<MDMovementComponent> MovementComponent;
};
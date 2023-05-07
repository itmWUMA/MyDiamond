#pragma once

#include <memory>
#include "MDActor.h"
using namespace std;

class MDPlayerState;

class MDPawn : public MDActor
{
public:
    MDPawn() = default;
    MDPawn(const shared_ptr<MDPlayerState>& PlayerState);

    void InitPawn(const shared_ptr<MDPlayerState>& PlayerState);

private:
    shared_ptr<MDPlayerState> PlayerState;
};
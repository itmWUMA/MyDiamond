#pragma once

#include <memory>
using namespace std;

class MDPlayerState;

class MDPawn
{
public:
    MDPawn() = default;
    MDPawn(const shared_ptr<MDPlayerState>& PlayerState);

    void InitPawn(const shared_ptr<MDPlayerState>& PlayerState);

private:
    shared_ptr<MDPlayerState> PlayerState;
};
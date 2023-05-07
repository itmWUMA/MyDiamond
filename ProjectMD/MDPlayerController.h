#pragma once

#include <memory>
using namespace std;

class MDPlayerState;

class MDPlayerController
{
public:
    MDPlayerController() = default;
    MDPlayerController(const shared_ptr<MDPlayerState>& PlayerState);

    void InitPlayerController(const shared_ptr<MDPlayerState>& PlayerState);

private:
    shared_ptr<MDPlayerState> PlayerState;
};


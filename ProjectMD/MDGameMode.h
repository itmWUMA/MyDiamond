#pragma once

#include <memory>
using namespace std;

class MDPawn;
class MDPlayerController;
class MDPlayerState;

class MDGameMode
{
public:
    MDGameMode(const shared_ptr<MDPawn>& DefaultPawn, 
        const shared_ptr<MDPlayerController>& PlayerController,
        const shared_ptr<MDPlayerState>& PlayerState);

private:
    shared_ptr<MDPawn> DefaultPawn;
    shared_ptr<MDPlayerController> PlayerController;
    shared_ptr<MDPlayerState> PlayerState;
};


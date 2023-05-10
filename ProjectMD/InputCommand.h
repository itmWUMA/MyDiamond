#pragma once

#include <memory>
#include "MDDefines.h"
using namespace std;

class MDPlayerController;

class IInputCommand
{
public:
    virtual ~IInputCommand() = default;
    virtual void Execute() = 0;

protected:
    weak_ptr<MDPlayerController> PlayerControllerCache;
};

class MDMoveCommand : public IInputCommand
{
public:
    MDMoveCommand(const weak_ptr<MDPlayerController>& PlayerControllerCahce, EMoveDirection Direction);
    virtual void Execute() override;

private:
    EMoveDirection Direction;
};
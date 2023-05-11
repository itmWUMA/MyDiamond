#pragma once

#include <memory>
#include "MDDefines.h"
using namespace std;

class MDPlayerController;

class IInputCommand
{
public:
    virtual ~IInputCommand() = default;
    virtual void Execute(const shared_ptr<MDPlayerController>& PlayerController) = 0;
};

class MDMoveCommand : public IInputCommand
{
public:
    MDMoveCommand(EMoveDirection Direction);
    virtual void Execute(const shared_ptr<MDPlayerController>& PlayerController) override;

private:
    EMoveDirection Direction;
};

class MDQuitGameCommand : public IInputCommand
{
public:
};
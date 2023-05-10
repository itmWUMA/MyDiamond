#pragma once

#include <memory>
using namespace std;

class IInputCommand;
class MDPlayerController;

class MDInputComponent
{
public:
    MDInputComponent(const weak_ptr<MDPlayerController>& OwnerCache);
    shared_ptr<IInputCommand> HandleInput() const;
};
#include "MDInputComponent.h"
#include <conio.h>
#include "MDPlayerController.h"
#include "InputCommand.h"
#include "MDDefines.h"

MDInputComponent::MDInputComponent(const weak_ptr<MDPlayerController>& OwnerCache)
    : OwnerCache(OwnerCache)
{
}

shared_ptr<IInputCommand> MDInputComponent::HandleInput() const
{
    const int FirstRead = _getch();
    if (FirstRead >= 0)
    {
        switch (FirstRead)
        {
            // UP
        case Keycode_W:
        case Keycode_w:
            return make_shared<MDMoveCommand>(OwnerCache, EMoveDirection::UP);
            // Left
        case Keycode_A:
        case Keycode_a:
            return make_shared<MDMoveCommand>(OwnerCache, EMoveDirection::LEFT);
            // Down
        case Keycode_S:
        case Keycode_s:
            return make_shared<MDMoveCommand>(OwnerCache, EMoveDirection::DOWN);
            // Right
        case Keycode_D:
        case Keycode_d:
            return make_shared<MDMoveCommand>(OwnerCache, EMoveDirection::RIGHT);
        default:
            return nullptr;
        }
    }

    const int SecondRead = _getch();
    switch (SecondRead)
    {
    case Keycode_Up:
        return make_shared<MDMoveCommand>(OwnerCache, EMoveDirection::UP);
    case Keycode_Left:
        return make_shared<MDMoveCommand>(OwnerCache, EMoveDirection::LEFT);
    case Keycode_Down:
        return make_shared<MDMoveCommand>(OwnerCache, EMoveDirection::DOWN);
    case Keycode_Right:
        return make_shared<MDMoveCommand>(OwnerCache, EMoveDirection::RIGHT);
    default:
        return nullptr;
    }
}

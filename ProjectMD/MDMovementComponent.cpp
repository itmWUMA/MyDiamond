#include "MDMovementComponent.h"

Vector2D MDMovementComponent::Move(const Vector2D& StartPosition, EMoveDirection Direction) const
{
    Vector2D EndPosition;
    switch (Direction)
    {
    case EMoveDirection::UP:
        EndPosition = Vector2D(StartPosition.first - Step, StartPosition.second);
        break;
    case EMoveDirection::RIGHT:
        EndPosition = Vector2D(StartPosition.first, StartPosition.second + Step);
        break;
    case EMoveDirection::DOWN:
        EndPosition = Vector2D(StartPosition.first + Step, StartPosition.second);
        break;
    case EMoveDirection::LEFT:
        EndPosition = Vector2D(StartPosition.first, StartPosition.second - Step);
        break;
    default:
        break;
    }
    return EndPosition;
}

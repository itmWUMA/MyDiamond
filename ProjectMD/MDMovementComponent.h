#pragma once

#include <memory>
#include "MDDefines.h"
using namespace std;

class MDMovementComponent
{
public:
    inline int GetStep() const { return DefaultStep; }
    inline void SetStep(int NewStep) { DefaultStep = NewStep; }

    /* Return unchecked owner's position before moving by step */
    Vector2D Move(const Vector2D& StartPosition, EMoveDirection Direction) const;
    Vector2D Move(const Vector2D& StartPosition, EMoveDirection Direction, int Step) const;

private:
    int DefaultStep = 1;
};


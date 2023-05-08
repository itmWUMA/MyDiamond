#pragma once

#include <memory>
#include "MDDefines.h"
using namespace std;

class MDMovementComponent
{
public:
    inline int GetStep() const { return Step; }
    inline void SetStep(int NewStep) { Step = NewStep; }

    /* Return unchecked owner's position before moving */
    Vector2D Move(const Vector2D& StartPosition, EMoveDirection Direction) const;

private:
    int Step = 1;
};


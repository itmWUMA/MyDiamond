#pragma once

#include "MDDefines.h"

class MDDiamond;

class MDPlayerState
{
public:
    MDPlayerState() = default;
    MDPlayerState(const Vector2D& DefaultSpawnPosition);
    inline Vector2D GetDefaultSpawnPosition() const { return DefaultSpawnPosition; }

public:
    int PlayerStepCount = 0;
    float Score = 0;
    shared_ptr<MDDiamond> AcquiredDiamond = nullptr;

private:
    Vector2D DefaultSpawnPosition;
};


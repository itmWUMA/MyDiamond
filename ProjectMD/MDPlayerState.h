#pragma once

#include "MDDefines.h"

class MDPlayerState
{
public:
    MDPlayerState() = default;
    MDPlayerState(const Vector2D& DefaultSpawnPosition);
    inline Vector2D GetDefaultSpawnPosition() const { return DefaultSpawnPosition; }

public:
    int PlayerStepCount = 0;
    int Score = 0;

private:
    Vector2D DefaultSpawnPosition;
};


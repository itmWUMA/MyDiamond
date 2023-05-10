#pragma once

#include "MDDefines.h"

class MDPlayerState
{
public:
    MDPlayerState() = default;
    MDPlayerState(const Vector2D& DefaultSpawnPosition);
    inline Vector2D GetDefaultSpawnPosition() const { return DefaultSpawnPosition; }

private:
    Vector2D DefaultSpawnPosition;
};


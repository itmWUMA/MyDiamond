#pragma once

#include "MDDefines.h"

class MDDiamond;

class MDPlayerState
{
public:
    MDPlayerState(const json11::Json& ConfigJson);
    inline Vector2D GetDefaultSpawnPosition() const { return DefaultSpawnPosition; }

public:
    int PlayerStepCount = 0;
    float Score = 0;
    shared_ptr<MDDiamond> AcquiredDiamond = nullptr;

private:
    static bool CheckConfig(const json11::Json& ConfigJson);

private:
    Vector2D DefaultSpawnPosition;
};


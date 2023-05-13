#include "MDPlayerState.h"

MDPlayerState::MDPlayerState(const json11::Json& ConfigJson)
{
    if (CheckConfig(ConfigJson))
    {
        const int X = ConfigJson["DefaultPosition"].array_items()[0].int_value();
        const int Y = ConfigJson["DefaultPosition"].array_items()[1].int_value();
        DefaultSpawnPosition = Vector2D(X, Y);
    }
}

bool MDPlayerState::CheckConfig(const json11::Json& ConfigJson)
{
    return ConfigJson["DefaultPosition"].is_array()
        && ConfigJson["DefaultPosition"].array_items()[0].is_number();
}

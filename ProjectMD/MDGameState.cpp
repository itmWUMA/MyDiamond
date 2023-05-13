#include "MDGameState.h"
#include "MDDiamond.h"

MDGameState::MDGameState(const json11::Json& ConfigJson)
{
    if (CheckConfig(ConfigJson))
    {
        DeadLine = ConfigJson.int_value();
    }
}

bool MDGameState::CheckConfig(const json11::Json& ConfigJson)
{
    return ConfigJson.is_number();
}

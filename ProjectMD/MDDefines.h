#pragma once

#include <utility>
using namespace std;

enum class EDiamondType
{
    TYPE_ONE = 0x1,
    TYPE_TWO = 0x2,
    TYPE_THREE = 0x4,
    TYPE_FOUR = 0x8,
    TYPE_FIVE = 0x10,
};

enum class EMoveDirection
{
    UP = 0x1,
    RIGHT = 0x2,
    DOWN = 0x4,
    LEFT = 0x8,
};

typedef pair<int, int> Vector2D;

#define DEBUG_LOG_PATH "./debug/log.txt"
#define DEBUG_FUNC_SIGN ((string(__FUNCTION__) + string("\n")).c_str())
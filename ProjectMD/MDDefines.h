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

typedef pair<int, int> Vector2D;
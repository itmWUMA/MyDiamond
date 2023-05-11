#pragma once

#include <utility>
#include "MDGameInstance.h"
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

constexpr int Keycode_A = 65;
constexpr int Keycode_W = 87;
constexpr int Keycode_S = 83;
constexpr int Keycode_D = 68;
constexpr int Keycode_a = 97;
constexpr int Keycode_w = 119;
constexpr int Keycode_s = 115;
constexpr int Keycode_d = 100;
constexpr int Keycode_Up = 72;
constexpr int Keycode_Down = 80;
constexpr int Keycode_Left = 75;
constexpr int Keycode_Right = 77;
constexpr int Keycode_Esc = 27;
constexpr int Keycode_DirectionKey_FirstInputCode = 224;

#define DEBUG_LOG_PATH "./debug/log.txt"
#define DEBUG_FUNC_SIGN ((string(__FUNCTION__) + string("\n")).c_str())
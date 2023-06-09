#pragma once

#include <utility>
#include "MDGameInstance.h"
using namespace std;

enum class EDiamondType
{
    TYPE_ONE = 0x1,
    TYPE_TWO = 0x2,
    TYPE_THREE = 0x3,
    TYPE_FOUR = 0x4,
    TYPE_FIVE = 0x5,
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
constexpr int Keycode_E = 69;
constexpr int Keycode_e = 101;
constexpr int Keycode_Y = 89;
constexpr int Keycode_y = 121;
constexpr int Keycode_N = 78;
constexpr int Keycode_n = 110;
constexpr int Keycode_DirectionKey_FirstInputCode = 224;

#define DEBUG_LOG_PATH "./debug/log.txt"
#define DEBUG_FUNC_SIGN ((string(__FUNCTION__) + string("\n")).c_str())
#define CONFIG_PATH "./config/config.json"
#define SAVE_DATA_PATH "./save/data.sav"
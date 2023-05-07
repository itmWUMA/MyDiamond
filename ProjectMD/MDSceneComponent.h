#pragma once

#include <utility>
using namespace std;

class MDSceneComponent
{
public:
    typedef pair<int, int> Vector2D;

public:
    inline int GetX() const { return Position.first; }
    inline int GetY() const { return Position.second; }
    inline Vector2D GetVector() const { return Position; }
    inline void SetX(int X) { Position.first = X; }
    inline void SetY(int Y) { Position.second = Y; }
    inline void SetVector(const Vector2D& Vector) { Position = Vector; }

private:
    Vector2D Position = make_pair(0, 0);
};
#pragma once

#include <memory>
using namespace std;

class MDSceneComponent;

class MDActor
{
public:
    MDActor();

public:
    std::shared_ptr<MDSceneComponent> SceneComponent;
};


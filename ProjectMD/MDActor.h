#pragma once

#include <memory>
using namespace std;

class MDSceneComponent;

class MDActor
{
public:
    MDActor();
    virtual ~MDActor() = default;
    virtual void Render() const {}

public:
    std::shared_ptr<MDSceneComponent> SceneComponent;
};


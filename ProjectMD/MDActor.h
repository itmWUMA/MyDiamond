#pragma once

#include <memory>
using namespace std;

class MDSceneComponent;
enum class EMoveDirection;

class MDActor
{
public:
    MDActor();
    virtual ~MDActor() = default;
    virtual void Render() const {}

protected:
    virtual shared_ptr<MDActor> GetSideActor(EMoveDirection Direction) const;

public:
    std::shared_ptr<MDSceneComponent> SceneComponent;
};


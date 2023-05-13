#pragma once

#include <memory>
class MDGameState;
class MDPlayerState;
using namespace std;

class MDUserWidget
{
public:
    virtual ~MDUserWidget();
    virtual void Render() const;

protected:
    static void RenderNewLine();
};

class MDGameEntryUI : public MDUserWidget
{
public:
    virtual void Render() const override;
};

class MDMainUI : public MDUserWidget
{
public:
    MDMainUI(const weak_ptr<MDPlayerState>& PlayerStateCache, const weak_ptr<MDGameState>& GameStateCache);
    virtual void Render() const override;

private:
    void RenderHeader() const;
    void RenderGameInfo() const;

private:
    weak_ptr<MDPlayerState> PlayerStateCache;
    weak_ptr<MDGameState> GameStateCache;
    const char* HeaderInfo = "MY DIAMOND\titmWUMA";
};

class MDGameOverUI : public MDUserWidget
{
public:
    virtual void Render() const override;
};

class MDPlayEndUI : public MDUserWidget
{
public:
    virtual void Render() const override;
};
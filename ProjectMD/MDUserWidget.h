#pragma once

#include <memory>
class MDGameState;
class MDPlayerState;
using namespace std;

class MDUserWidget
{
public:
    MDUserWidget() = default;
    void InitUserWidget(const weak_ptr<MDPlayerState>& PlayerStateCache, const weak_ptr<MDGameState>& GameStateCache);
    void Render() const;
    void RenderQuitUI() const;

private:
    void RenderHeader() const;
    void RenderGameInfo() const;
    static void RenderNewLine();

private:
    weak_ptr<MDPlayerState> PlayerStateCache;
    weak_ptr<MDGameState> GameStateCache;
    const char* HeaderInfo = "MY DIAMOND\titmWUMA";
};

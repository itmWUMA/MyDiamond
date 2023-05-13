#include "MDUserWidget.h"

#include <iostream>

#include "MDDebugger.h"
#include "MDDiamond.h"
#include "MDGameState.h"
#include "MDPlayerState.h"
#include "MDScene.h"

MDUserWidget::~MDUserWidget()
{
#if _DEBUG
    MDDebugger::Log(DEBUG_FUNC_SIGN);
#endif
}
void MDUserWidget::Render() const
{
    system("cls");
}

void MDUserWidget::RenderNewLine()
{
    cout << '\n';
    cout << '\n';
}

void MDMainUI::RenderHeader() const
{
    cout << HeaderInfo;
}

void MDMainUI::RenderGameInfo() const
{
    if (!PlayerStateCache.expired() && !GameStateCache.expired())
    {
        cout << "Turn " << GameStateCache.lock()->GetTurnCount() << '\t';
        cout << "Score = " << PlayerStateCache.lock()->Score << '\t';
        const shared_ptr<MDPlayerState> PlayerState = PlayerStateCache.lock();
        if (PlayerState->AcquiredDiamond)
        {
            PlayerState->AcquiredDiamond->Render();
        }
    }
}

void MDGameEntryUI::Render() const
{
    MDUserWidget::Render();
}

MDMainUI::MDMainUI(const weak_ptr<MDPlayerState>& PlayerStateCache, const weak_ptr<MDGameState>& GameStateCache)
    : PlayerStateCache(PlayerStateCache), GameStateCache(GameStateCache)
{
}

void MDMainUI::Render() const
{
    MDUserWidget::Render();

    // First Line
    RenderHeader();
    RenderNewLine();
    // Second Line
    RenderGameInfo();
    RenderNewLine();
    // Scene
    MDScene::Get()->RenderSence();
}

void MDGameOverUI::Render() const
{
    MDUserWidget::Render();

    cout << "You DIE~~~";
    RenderNewLine();
}

void MDPlayEndUI::Render() const
{
    MDUserWidget::Render();

    cout << "GOODBYE~~~";
    RenderNewLine();
}
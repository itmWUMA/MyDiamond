#include "MDUserWidget.h"

#include <iostream>

#include "MDGameState.h"
#include "MDPlayerState.h"
#include "MDScene.h"

void MDUserWidget::InitUserWidget(const weak_ptr<MDPlayerState>& PlayerStateCache,
                                  const weak_ptr<MDGameState>& GameStateCache)
{
    this->GameStateCache = GameStateCache;
    this->PlayerStateCache = PlayerStateCache;
}

void MDUserWidget::Render() const
{
    system("cls");
    // First Line
    RenderHeader();
    RenderNewLine();
    // Second Line
    RenderGameInfo();
    RenderNewLine();
    // Scene
    MDScene::Get()->RenderSence();
}

void MDUserWidget::RenderHeader() const
{
    cout << HeaderInfo;
}

void MDUserWidget::RenderGameInfo() const
{
    if (!PlayerStateCache.expired() && !GameStateCache.expired())
    {
        cout << "Turn " << GameStateCache.lock()->TurnCount << '\t';
        cout << "Score = " << PlayerStateCache.lock()->Score;
    }
}

void MDUserWidget::RenderNewLine()
{
    cout << '\n';
    cout << '\n';
}

void MDUserWidget::RenderQuitUI() const
{
    system("cls");
    cout << "GOODBYE~~~";
    RenderNewLine();
}
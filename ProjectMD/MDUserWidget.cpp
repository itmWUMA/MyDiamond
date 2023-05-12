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
        cout << "Turn " << GameStateCache.lock()->GetTurnCount() << '\t';
        cout << "Score = " << PlayerStateCache.lock()->Score << '\t';
        const shared_ptr<MDPlayerState> PlayerState = PlayerStateCache.lock();
        if (PlayerState->AcquiredDiamond)
        {
            PlayerState->AcquiredDiamond->Render();
        }
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
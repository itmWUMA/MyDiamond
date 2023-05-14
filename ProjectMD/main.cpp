#include <memory>

#include "MDGameInstance.h"
using namespace std;

int main(int argc, char* argv[])
{
    bool bRestartGame = false;
    do
    {
        GameInstance = make_unique<MDGameInstance>();
        GameInstance->Play();
        bRestartGame = GameInstance->IsRestartGame();
    } while (bRestartGame);

    return 0;
}

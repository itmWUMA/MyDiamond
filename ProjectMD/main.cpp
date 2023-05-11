#include <memory>

#include "MDGameInstance.h"
using namespace std;

int main(int argc, char* argv[])
{
    GameInstance = new MDGameInstance;
    GameInstance->Play();

    return 0;
}

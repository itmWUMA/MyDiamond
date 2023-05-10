#include <memory>
#include "MDGameInstance.h"
using namespace std;

int main(int argc, char* argv[])
{
    const unique_ptr<MDGameInstance> GameInstance = make_unique<MDGameInstance>();
    GameInstance->Play();

    return 0;
}

#pragma once

#include <fstream>
using namespace std;

#if _DEBUG
class MDDebugger
{
public:
    static void Log(const char* Text);

private:
    static bool bStartLog;
};
#endif
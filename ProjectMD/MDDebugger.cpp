#include "MDDebugger.h"
#include "MDDefines.h"

#if _DEBUG
bool MDDebugger::bStartLog = false;

void MDDebugger::Log(const char* Text)
{
    ofstream LogFileStream;
    if (bStartLog)
    {
        LogFileStream.open(DEBUG_LOG_PATH, ios::app);
        if (LogFileStream.is_open())
        {
            LogFileStream << Text;
        }
        LogFileStream.close();
    }
    else
    {
        LogFileStream.open(DEBUG_LOG_PATH, ios::out);
        if (LogFileStream.is_open())
        {
            LogFileStream << Text;
        }
        LogFileStream.close();
        bStartLog = true;
    }
}
#endif
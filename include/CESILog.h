#ifndef CESILOG_H_
#define CESILOG_H_

#include <iostream>
#include <fstream>
#include <time.h>
#include <string.h>

using std::string;

//Control Variables Part
namespace LogControl{
    bool isPrintLogToConsole = false;
    std::ofstream logFileStream;
    int globalLogLevel = 0;
    string defaultLogPath="CESI.log";//Could change to absolute path when need
}

//Private Functions Part
namespace LogPrivateFunc{

    inline string GetLongTimeStr(){
        time_t curTimeTmp; time(&curTimeTmp);
        string curTimeStr = asctime(localtime(&curTimeTmp));
        curTimeStr.pop_back();
        return curTimeStr;
    }
    
    inline string GetShortTimeStr(){
        time_t curTimeTmp; time(&curTimeTmp);
        tm* curTime = localtime(&curTimeTmp);
        char curTimeStr[256];
        snprintf(curTimeStr, 256, "%02d:%02d:%02d", curTime->tm_hour, curTime->tm_min, curTime->tm_sec);
        return curTimeStr;
    }
}

//Declaration Part

void LogFileInit(string _logPath);
inline void PrintLogHeader();
inline void PrintLog(string body, int level);

//Definition Part

void LogFileInit(string _logPath=LogControl::defaultLogPath){
    using namespace std;
    using namespace LogControl;

    if(isPrintLogToConsole == false)
    {
        logFileStream.open(_logPath,ios::app|ios::out);
        clog.rdbuf(logFileStream.rdbuf());
    }
}

inline void PrintLogHeader(){
    using namespace std;
    using namespace LogPrivateFunc;

    clog << "\nCESI Runtime Log (" << GetLongTimeStr() << ")" << endl;
    clog << "===========================================================" << endl;
}

//level:
//-1:Debug 0:Info 1:Warning 2:Error 3:Fatal
inline void PrintLog(string body, int level=0){
    using namespace std;
    using namespace LogControl;
    using namespace LogPrivateFunc;

    if(level < globalLogLevel) return;

    clog << GetShortTimeStr() << " | ";

    #ifdef PROG_NAME
    clog << PROG_NAME << " : ";
    #endif

    switch(level)
    {
        case -1:
            clog << "[Debug] ";
            break;
        case 0:
            clog << "[Info] ";
            break;
        case 1:
            clog << "[Warning] ";
            break;
        case 2:
            clog << "[Error] ";
            break;
        case 3:
            clog << "[Fatal] ";
            break;
        default:
            clog << "[Custom] ";
            break;
    }
    
    clog << body << endl;
}

#endif
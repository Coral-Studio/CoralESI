#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#define PROG_NAME "CESI_entrypoint"

#include <windows.h>
#include "include/CESILog.h"
#include "include/CESIPath.h"

using namespace std;

int main(int argc, char* argv[]){
    SetCurrentDirectory(GetExecFileFolder().c_str());
    
    LogFileInit();

    PrintLogHeader();
    
    PrintLog("CESI start");

    if(IsPathExist("DISABLE")){
        PrintLog("DISABLE file detected, exit");
        exit(0);
    }
    
    PrintLog("Activate CESI_run");
    auto ret = ShellExecute(
        NULL,
        (TCHAR*)"runas",
        (TCHAR*)RelativePath2AbsolutePath("CESI_run\\CESI_run").c_str(),
        NULL,
        (TCHAR*)RelativePath2AbsolutePath("CESI_run").c_str(),
        SW_HIDE
    );
    if((INT_PTR)ret <= 32) PrintLog("Failed to activate CESI_run", 2);

    PrintLog("Activate CESI_install");
    ret = ShellExecute(
        NULL,
        (TCHAR*)"runas",
        (TCHAR*)RelativePath2AbsolutePath("CESI_install\\CESI_install").c_str(),
        NULL,
        (TCHAR*)RelativePath2AbsolutePath("CESI_install").c_str(),
        SW_HIDE
    );
    if((INT_PTR)ret <= 32) PrintLog("Failed to activate CESI_install", 2);

    return 0;
}
#define PROG_NAME "CESI_run"

#include <windows.h>
#include <iostream>
#include "../include/CESILog.h"
#include "../include/CESIPath.h"
#include<direct.h>

using namespace std;

int main(int argc, char* argv[]){
    SetCurrentDirectory((GetExecFileFolder() + "\\..").c_str());

    LogFileInit();

    PrintLog("Run commands in CESI_run.manifest");

    ifstream manifest;
    manifest.open("CESI_run\\CESI_run.manifest", ios::in);
    if(!manifest)
    {
        PrintLog("Failed to open CESI_run.manifest", 3);
        exit(1);
    }
    
    string _command, _filepath, _parameters;
    while(getline(manifest, _command))
    {
        if(_command == "CESI_EOF_MARK")
        {
            exit(0);
        }

        PrintLog("Run command: " + _command);

        int _separator_index = _command.find_first_of('|');
        if(_separator_index == string::npos){
            _filepath = _command;
            _parameters = "";
        }
        else{
            _filepath = _command.substr(0, _separator_index);
            _parameters = _command.substr(_separator_index+1, (_command.size()-1)-(_separator_index+1)+1);
        }

        SHELLEXECUTEINFO se;
        memset(&se, 0, sizeof(SHELLEXECUTEINFO));
        se.cbSize = sizeof(SHELLEXECUTEINFO);
        se.lpVerb = (TCHAR*)"runas";//Run as admin
        se.lpFile = (TCHAR*)_filepath.c_str();
        se.lpParameters = (TCHAR*)_parameters.c_str();
        se.lpDirectory = NULL;//Reserved
        se.nShow = SW_HIDE;//SW_SHOW when debugging

        if(!ShellExecuteEx(&se)) PrintLog("Failed to run command: " + _command, 2);
    }

    PrintLog("File ends without CESI_EOF_MARK mark", 1);

    return 0;
}
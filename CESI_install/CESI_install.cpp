#define PROG_NAME "CESI_install"

#include <windows.h>
#include <vector>
#include <assert.h>
#include "../include/CESILog.h"
#include "../include/CESIPath.h"
#include "../include/CESIRegOpt.h"

using namespace std;

vector<string>CommandSplit(string cmd){
    vector<string>ret;
    string cur;
    for(int i=0;i<cmd.size();i++)
    {
        if(cmd[i] == '|')
        {
            ret.push_back(cur);
            cur.clear();
        }
        else
        {
            cur += cmd[i];
        }
    }
    if(!cur.empty()) ret.push_back(cur);
    return ret;
}

int DoCommand(vector<string>cmd){
    assert(!cmd.empty());
    if(cmd[0] == "COPY")
    {
        if(!(4<=cmd.size() && cmd.size()<=4))
        {
            PrintLog("Wrong format of command: " + cmd[0], 2);
            return 1;
        }
        if(cmd[3] == "Folder")
        {
            STARTUPINFO si={sizeof(si)};
            PROCESS_INFORMATION pi;
            BOOL ret = CreateProcess(NULL,(TCHAR*)("xcopy \"" + cmd[1]+ "\" \"" + cmd[2] + "\" /E /I /Y /C").c_str(),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&si,&pi); 
            if(ret == TRUE)
            {
                WaitForSingleObject(pi.hThread,60*1000); 
                CloseHandle(pi.hThread); 
                CloseHandle(pi.hProcess); 
            }
            else
            {
                PrintLog("Failed to copy", 2);
                return 1;
            }
        }
        else if(cmd[3] == "File")
        {
            if(!IsPathExist(cmd[2]))
            {
                STARTUPINFO _si={sizeof(_si)};
                PROCESS_INFORMATION _pi;
                BOOL _ret = CreateProcess(NULL,(TCHAR*)("cmd.exe /c mkdir \"" + cmd[2] + "\"").c_str(),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&_si,&_pi); 
                if(_ret == TRUE)
                {
                    WaitForSingleObject(_pi.hThread,60*1000); 
                    CloseHandle(_pi.hThread); 
                    CloseHandle(_pi.hProcess); 
                }
                else
                {
                    PrintLog("Failed to copy", 2);
                    return 1;
                }
                Sleep(50);
            }
            STARTUPINFO si={sizeof(si)};
            PROCESS_INFORMATION pi;
            BOOL ret = CreateProcess(NULL,(TCHAR*)("xcopy \"" + cmd[1]+ "\" \"" + cmd[2] + "\" /Y /C").c_str(),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&si,&pi); 
            if(ret == TRUE)
            {
                WaitForSingleObject(pi.hThread,60*1000); 
                CloseHandle(pi.hThread); 
                CloseHandle(pi.hProcess); 
            }
            else
            {
                PrintLog("Failed to copy", 2);
                return 1;
            }
        }
        else
        {
            PrintLog("Wrong type of file", 2);
            return 1;
        }
    }
    else if(cmd[0] == "REG")
    {
        PrintLog("Option 'REG' still in development, exit", 1);
        return 1;

        if(!(7<=cmd.size() && cmd.size()<=7))
        {
            PrintLog("Wrong format of command: " + cmd[0], 2);
            return 1;
        }
        if(cmd[1]=="ADD" || cmd[1]=="CHG")
        {

        }
        else if(cmd[1] == "DEL")
        {

        }
        else
        {
            PrintLog("Unrecognized option: " + cmd[1], 2);
            return 1;
        }
    }
    else if(cmd[0] == "RUN")
    {
        if(!(2<=cmd.size() && cmd.size()<=3))
        {
            PrintLog("Wrong format of command: " + cmd[0], 2);
            return 1;
        }

        STARTUPINFO si={sizeof(si)};
        PROCESS_INFORMATION pi;
        BOOL ret = CreateProcess(NULL,(TCHAR*)cmd[1].c_str(),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&si,&pi); 
        if(ret == TRUE)
        {
            if(cmd.size()>2 && cmd[2] == "WAIT") WaitForSingleObject(pi.hThread,INFINITE); 
            CloseHandle(pi.hThread); 
            CloseHandle(pi.hProcess); 
        }
        else
        {
            PrintLog("Failed to run command: " + cmd[1], 2);
            return 1;
        }
    }
    else if(cmd[0] == "EXEC")
    {
        if(!(4<=cmd.size() && cmd.size()<=4))
        {
            PrintLog("Wrong format of command: " + cmd[0], 2);
            return 1;
        }
        SHELLEXECUTEINFO se;
        memset(&se, 0, sizeof(SHELLEXECUTEINFO));
        se.cbSize = sizeof(SHELLEXECUTEINFO);
        se.lpVerb = (TCHAR*)"runas";//Run as admin
        se.lpFile = (TCHAR*)cmd[1].c_str();
        se.lpParameters = (TCHAR*)cmd[2].c_str();
        se.lpDirectory = NULL;//Reserved
        se.nShow = (cmd[3]=="SHOW"?SW_SHOW:SW_HIDE);
        if(!ShellExecuteEx(&se)) PrintLog("Failed to run command: " + cmd[1] + " " +cmd[2], 2);
    }
    else if(cmd[0] == "CMD")
    {
        if(!(2<=cmd.size() && cmd.size()<=3))
        {
            PrintLog("Wrong format of command: " + cmd[0], 2);
            return 1;
        }

        STARTUPINFO si={sizeof(si)};
        PROCESS_INFORMATION pi;
        BOOL ret = CreateProcess(NULL,(TCHAR*)("cmd.exe /c" + cmd[1]).c_str(),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&si,&pi); 
        if(ret == TRUE)
        {
            if(cmd.size()>2 && cmd[2] == "WAIT") WaitForSingleObject(pi.hThread,INFINITE); 
            CloseHandle(pi.hThread); 
            CloseHandle(pi.hProcess); 
        }
        else
        {
            PrintLog("Failed to run command: " + cmd[1], 2);
            return 1;
        }
    }
    else if(cmd[0] == "SLEEP")
    {
        if(!(2<=cmd.size() && cmd.size()<=2))
        {
            PrintLog("Wrong format of command: " + cmd[0], 2);
            return 1;
        }

        Sleep(atoi(cmd[1].c_str()));
    }
    else
    {
        PrintLog("Unrecognized command: " + cmd[0], 2);
        return 1;
    }
    return 0;
}

int DoInstall(string _path){
    if(!SetCurrentDirectory((GetExecFileFolder()+"\\"+_path).c_str()))
    {
        PrintLog("No folder named " + _path, 2);
        return 1;
    }

    ifstream list;
    list.open("CESI_INSTALL_LIST");
    if(!list)
    {
        PrintLog("Failed to open CESI_INSTALL_LIST", 2);
        return 1;
    }

    string _command;
    getline(list, _command);
    if(_command != "CESI_INSTALL_LIST_FORMATVERSION_1")
    {
        PrintLog("CESI_INSTALL_LIST header not found", 2);
        return 1;
    }
    while(getline(list, _command)){
        if(_command == "CESI_EOF_MARK") return 0;
        if(_command.front() == '#') continue;

        PrintLog("Run command: " + _command, -1);

        auto ret = CommandSplit(_command);
        if(ret.empty())
        {
            PrintLog("Blank command/line", 1);
            continue;
        }
        if(DoCommand(ret))
        {
            PrintLog("Failed to excute: \"" + _command + "\". But still trying to excute the remaining commands.", 2);
            // PrintLog("Failed to excute: \"" + _command + "\".", 2);
            // return 1;
        }
    }

    PrintLog("CESI_INSTALL_LIST ends without CESI_EOF_MARK mark", 1);

    return 0;
}

int main(int argc, char* argv[]){
    SetCurrentDirectory(GetExecFileFolder().c_str());

    // LogControl::globalLogLevel=-1;

    LogFileInit("..\\CESI.log");

    PrintLog("Loading installation folders in CESI_install.manifest");

    ifstream manifest;
    manifest.open("CESI_install.manifest", ios::in);
    if(!manifest)
    {
        PrintLog("Failed to open CESI_install.manifest", 3);
        exit(1);
    }
    
    string _curline;
    while(getline(manifest, _curline))
    {
        if(_curline == "CESI_EOF_MARK") exit(0);
        if(_curline.front() == '#') continue;

        PrintLog("Try to install " + _curline);
        if(DoInstall(_curline)) PrintLog("Cannot install " + _curline, 2);
        else PrintLog(_curline + " installed");
    }

    PrintLog("CESI_install.manifest ends without CESI_EOF_MARK mark", 1);

    return 0;
}
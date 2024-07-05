#ifndef CESIPATH_H_
#define CESIPATH_H_

#include <iostream>
#include <windows.h>
#include <string.h>
#include <io.h>

using std::string;

//Declaration Part

inline string GetFileNameFromPath(string path);
inline string GetFileFolderFromPath(string path);
inline string GetExecFilePath();
inline string GetExecFileFolder();
inline string RelativePath2AbsolutePath(string _path);
bool IsPathExist(string csPath);

//Definition Part

inline string GetFileNameFromPath(string path){
	int index = path.find_last_of('\\');
	string res = path.substr(index + 1, path.size() - (index + 1));
	return res;
}

inline string GetFileFolderFromPath(string path){
	int index = path.find_last_of('\\');
	string res = path.substr(0, index);
	return res;
}

inline string GetExecFilePath(){
    char _path[256];
    GetModuleFileName(NULL, _path, 256);
    return _path;
}

inline string GetExecFileFolder(){
	return GetFileFolderFromPath(GetExecFilePath());
}

inline string RelativePath2AbsolutePath(string _path){
    return GetExecFileFolder() + "\\" + _path;
}

bool IsPathExist(string csPath){
	int nRet = _access(csPath.c_str(), 0);
	return 0 == nRet || EACCES == nRet;
}


#endif
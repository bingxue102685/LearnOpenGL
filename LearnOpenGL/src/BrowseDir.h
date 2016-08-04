#ifndef _BROW_DIR_H_
#define _BROW_DIR_H_

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <direct.h>
#include <Windows.h>

using namespace std;

class BrowseDir
{
private:
	//BrowseDir(string rootName);
	BrowseDir();
	string curRootName;
	string curRootPath;
	static BrowseDir* browseDir;
	void doSomethingWhenFind(string fileName);
	map<string, string> filePath;
	vector<string> fileNames;
	int fileCount;
	bool initFileInfo();
	void setRootPath(string rootName);
public:
	static BrowseDir* getInstance(string rootName);
	map<string, string> getAllFilePath();
	vector<string> getAllFileNames();
};



#endif //_BROW_DIR_H_
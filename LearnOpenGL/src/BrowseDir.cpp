#include "BrowseDir.h"

BrowseDir* BrowseDir::browseDir = nullptr;

BrowseDir::BrowseDir()
{
}

BrowseDir* BrowseDir::getInstance(string rootName)
{
	if (BrowseDir::browseDir == nullptr)
	{
		BrowseDir::browseDir = new BrowseDir();
	}
	BrowseDir::browseDir->setRootPath(rootName);
	BrowseDir::browseDir->initFileInfo();
	return BrowseDir::browseDir;
}

void BrowseDir::setRootPath(string rootName)
{
	this->curRootName = rootName;
	char* curretPath = getcwd(nullptr, 0);
	this->curRootPath = string(curretPath) + "\\..\\resource\\" + this->curRootName;
}


bool BrowseDir::initFileInfo()
{
	filePath.clear();
	fileNames = vector<string>(6);
	WIN32_FIND_DATAA findData;
	HANDLE findRet;
	string researchPath = this->curRootPath + "\\*.*";
	findRet = FindFirstFile(researchPath.c_str(), &findData);

	if (INVALID_HANDLE_VALUE == findRet) {
		cout << "file research failed！" << endl;
		return false;
	}

	while ( FindNextFile(findRet, &findData) ) {
		//去除. 和 .. 去除文件夹
		//if ((strcmp(findData.cFileName, ".") == 0) || (strcmp(findData.cFileName, "..") == 0))
		if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			continue;
		}
		//处理
		doSomethingWhenFind(findData.cFileName);

		cout << findData.cFileName << endl;
	};
}


void BrowseDir::doSomethingWhenFind(string fileName)
{
	string tempPath = this->curRootPath + "\\" + fileName;
	string tempKey = "";
	//fileName  按 右，左，上，下，前，后
	//右
	if (fileName.find("right") != string::npos) {
		tempKey = "right";
		fileNames[0] = "right";
	}
	//左
	if (fileName.find("left") != string::npos) {
		tempKey = "left";
		fileNames[1] = "left";
	}
	//上
	if (fileName.find("top") != string::npos) {
		tempKey = "top";
		fileNames[2] = "top";
	}
	//下
	if (fileName.find("bottom") != string::npos) {
		tempKey = "bottom";
		fileNames[3] = "bottom";
	}
	//后
	if (fileName.find("back") != string::npos) {
		tempKey = "back";
		fileNames[4] = "back";
	}
	//前
	if (fileName.find("front") != string::npos) {
		tempKey = "front";
		fileNames[5] = "front";
	}
	filePath[tempKey] = tempPath;
}

map<string, string> BrowseDir::getAllFilePath()
{
	return filePath;
}

vector<string> BrowseDir::getAllFileNames()
{
	return fileNames;
}

//

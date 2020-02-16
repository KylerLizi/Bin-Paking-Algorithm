#include "FileManager.h"
#include "fstream"
#include "sstream"
#include "string"

CString FileManager::GetFilePath() {
	OPENFILENAME ofn;// 公共对话框结构
	char szFile[300];// 用来保存获取文件名称的缓冲区

	ZeroMemory(&ofn, sizeof(ofn));// 初始化选择文件对话框
	ofn.lStructSize = sizeof(ofn);//指定这个结构的大小，以字节为单位
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = (LPSTR)szFile;//打开的文件的全路径
	ofn.lpstrFile[0] = '\0';//第一个字符串是过滤器描述的显示字符串
	LPTSTR        lpstrCustomFilter;
	DWORD         nMaxCustFilter;
	ofn.nFilterIndex = 1;
	LPTSTR        lpstrFile;
	ofn.nMaxFile = sizeof(szFile);
	//ofn.lpstrFilter = (LPSTR)"ALL\0*.*\0Text\0*.TXT\0";//所有类型
	ofn.lpstrFilter = (LPSTR)"0Text\0*.TXT\0";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = (LPCSTR)"..\\TestData";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	CString filePath;
	if (GetOpenFileName(&ofn)) {
		//path_image = Lpcwstr2String((LPCWSTR)ofn.lpstrFile);//将一个LPCWSTR转换为string
		filePath.Format("%s", ofn.lpstrFile);
		return filePath;
	}
	else {
		return "";
	}
}

vector<vector<int>> FileManager::GetFileIntData(CString path)
{
	ifstream data(path);
	vector<vector<int>>res;
	string line;
	while (getline(data, line))
	{
		stringstream ss;//输入流
		ss << line;
		if (!ss.eof()) 
		{
			int temp;
			vector<int>blockInfo;
			while (ss >> temp)
				blockInfo.push_back(temp);
			res.push_back(blockInfo);
		}
	}
	return res;
}
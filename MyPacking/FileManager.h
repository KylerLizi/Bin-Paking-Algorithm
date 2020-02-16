#pragma once
#include <atlstr.h>//CString头文件
#include "vector"
using namespace std;

class FileManager
{
public:

	static CString GetFilePath();//打开一个窗口，选择一个TXT文件
	static vector<vector<int>> GetFileIntData(CString path);//读取txt中每行矩形的宽、高、数量

};


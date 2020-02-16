#include "PackManager.h"
#include "binPackingAlgorithm.h"
#include "stdlib.h"
#include "string"
#include "iostream"
#include "FileManager.h"
#include "glDraw.h"

int main()
{
	binPackingAlgorithm manager;

	//弹出窗口，选择测试数据集
	//------------------------------------------
	CString filePath = FileManager::GetFilePath();
	if (filePath == "")
		return 0;
	vector<vector<int>> bInfo = FileManager::GetFileIntData(filePath);
	int i;
	for (i = 0; i < bInfo.size(); i++)
		manager.AddBlocks(bInfo[i][0], bInfo[i][1], bInfo[i][2]);
	                                                                
	//矩形排版算法
	//------------------------------------------
	//对所有矩形按宽度排序
	int sortType;
	cout << "*********************************" << endl;
	cout << "**  请选择装箱问题的排序算法： **" << endl;
	cout << "**  1.矩形宽度优先             **" << endl;
	cout << "**  2.矩形高度优先             **" << endl;
	cout << "**  3.矩形面积优先             **" << endl;
	cout << "**  4.矩形最大边优先(最优)     **" << endl;
	cout << "**  输入例：1                  **" << endl;
	cout << "*********************************" << endl;
	cin >> sortType;
	switch (sortType)
	{
		case 1:manager.SortByWidth(); break;
		case 2:manager.SortByHeight(); break;
		case 3:manager.SortByArea(); break;
		case 4: default:manager.SortByMaxside(); break;
	}

	cout << endl << "------------排序前------------" << endl;
	manager.PrintBlocks();
	cout << endl << "------------排序后------------" << endl;
	manager.PrintBlocks();
	//逐个插入二叉树
	manager.Fit();
	//打印二叉树
	cout << endl << "------------打印矩阵二叉树------------" << endl;
	string prefix = "";
	manager.PrintTree(g_root, g_root, prefix);

	//opengl绘制结果
	//------------------------------------------
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//设置显示模式
	glutInitWindowSize(g_maxW, g_maxH); //设置窗口大小
	glutInitWindowPosition(200, 100);   //设置窗口在屏幕上的位置 
	glutCreateWindow("矩形排版结果"); //创建窗口并给出标题
	glutDisplayFunc(glDraw::render);   //注册显示窗口时回调函数renderScene
	glutMouseFunc(glDraw::LBClick);
	glOrtho(0.0f, g_maxW, 0.0f, g_maxH, 1.0, -1.0);//设置绘制时的输入最大值
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   //使用白色清空背景底
	glutMainLoop();     //消息循环（处理操作系统等的消息，例如键盘、鼠标事件等）

	cin >> prefix;//防止结束
	system("pause");
	return 0;
}
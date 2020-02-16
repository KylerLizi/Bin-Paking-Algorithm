#pragma once
#include "GL/glut.h"//记得配置改为Debug x86模式，不然配置完环境找不到该文件
#include "string"
using namespace std;
#define MAX_CHAR 128

struct BlockTree;
class glDraw
{
public:
	static void render();//渲染绘制图形
	static void PreOrderTraverse(BlockTree* node);//递归先序遍历二叉树
	static void StackPreOrderTraverse(BlockTree * node);//非递归先序遍历一次二叉树
	static string CalculateFilledArea(int width, int height);//计算矩形空间的利用率
	static void DrawRectangle(float leftBottomX, float leftBottomY, float rightTopX, float rightTopY);//绘制矩形
	static void DrawString(string str);//绘制英文、数字、符号
	static void LBClick(int button, int state, int x, int y);//每次点击绘制一个矩形
};


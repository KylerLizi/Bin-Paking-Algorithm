#pragma once
#include "GL/glut.h"
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
	static void LBClick(int button, int state, int x, int y);
};


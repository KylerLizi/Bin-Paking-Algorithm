#include "glDraw.h"
#include "cstdlib"
#include "PackStruct.h"
#include "stack"
#include "windows.h"

static stack<BlockTree*>sNode;

#define SHOW_ALL//是否一次性全部绘制,当想逐个绘制时，注释该句，单击窗口左键即可

void glDraw::render()
{
	glClear(GL_COLOR_BUFFER_BIT);//清空颜色缓冲池
#ifdef SHOW_ALL
	PreOrderTraverse(g_root);
	glRasterPos2f(30.0f, g_maxH - 30.f);//设置文字位置
	DrawString(CalculateFilledArea(0, 0));
#else
	sNode.push(g_root);//点击逐个显示
#endif
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSwapBuffers();

	glFlush();
}


void glDraw::PreOrderTraverse(BlockTree* node)
{//递归先序遍历二叉树
	if (node == NULL || node->isUsed == 0)
		return;
	//绘制矩形，输入左下角x,y右上角x,y坐标
	DrawRectangle(node->cur.x, g_maxH - node->cur.y - node->cur.h, node->cur.x + node->cur.w, g_maxH - node->cur.y);
	CalculateFilledArea(node->cur.w, node->cur.h);//计算当前的利用率
	PreOrderTraverse(node->left);
	PreOrderTraverse(node->right);
}

void glDraw::StackPreOrderTraverse(BlockTree* node)
{//每次左键点击输出栈中一个节点值
	if (node)
	{
		sNode.pop();
		if (node->isUsed)
			DrawRectangle(node->cur.x, g_maxH - node->cur.y - node->cur.h, node->cur.x + node->cur.w, g_maxH - node->cur.y);
		if (node->right)
			sNode.push(node->right);
		if (node->left)
			sNode.push(node->left);
	}
}

string glDraw::CalculateFilledArea(int width, int height)
 {
	 static int area;
	 area += width * height;//计算已占用的面积大小
	 int percentage = (int)((double)area / (g_maxW*g_maxH) * 100);
	 return "Filled:" + to_string(percentage).append("%");//从int到string
 }

void glDraw::DrawRectangle(float leftBottomX, float leftBottomY, float rightTopX, float rightTopY)
{
	float v = 1.0 / RAND_MAX;
	glColor3f(rand()*v, rand()*v, rand()*v);//设置随机颜色绘图
	glRectf(leftBottomX, leftBottomY, rightTopX, rightTopY);//绘制矩形
}

void glDraw::DrawString(string str)
{
	static int isFirstCall = 1;
	static GLuint lists;
	
	if (isFirstCall)
	{//第一次调用时 为每个ASCII字符生成一个显示列表
		isFirstCall = 0;
		//申请MAX__CHAR个连续的显示列表编号
		lists = glGenLists(MAX_CHAR);
		//把每个字符的绘制命令装到对应的显示列表中
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}

	//调用每个字符对应的显示列表，绘制每个字符
	for (int i=0; i<str.length(); i++)
		glCallList(lists + str.at(i));
}

void glDraw::LBClick(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
		if (button == GLUT_LEFT_BUTTON)
		{
			if (!sNode.empty())
			{
				//CalculateFilledArea(sNode.top()->cur.w, sNode.top()->cur.h);
				StackPreOrderTraverse(sNode.top());
			}
			glFlush();
		} 
}
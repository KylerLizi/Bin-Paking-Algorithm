#pragma once
struct BlockInfo {//矩形的位置与大小
	int x;//x坐标
	int y;//y坐标
	int w;//宽度
	int h;//高度
};

struct BlockTree {//矩形二叉树节点
	BlockInfo cur;//根节点
	int isUsed;
	int isLeft;
	BlockTree* right;//右子树是空矩形的下边的区域
	BlockTree* left;//左子树是空矩形的右边的区域
};

extern BlockTree* g_root;//根节点
extern int g_maxW, g_maxH;//当前矩形框的最大大小

class PackStruct
{
};


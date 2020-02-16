#pragma once
struct BlockInfo {//矩形的位置与大小
	int x;//x坐标
	int y;//y坐标
	int w;//宽度
	int h;//高度
};

struct BlockTree {//矩形二叉树节点
	BlockInfo cur;//根节点
	int isUsed;//该矩形空间是否被占用
	int isLeft;
	BlockTree* right;//右子树是空矩形的下边的区域 当该节点是叶子节点时，right指向下一个叶子
	BlockTree* left;//左子树是空矩形的右边的区域
};

extern BlockTree* g_root;//根节点
//叶子链表头节点，第一个节点从->right开始，单向链表,left不用
//TODO：当矩形拆分成小矩形时 顺序很重要  g_root和g_leaf要处理同一颗二叉树
extern BlockTree* g_leaf_head;
extern int g_maxW, g_maxH;//当前矩形框的最大大小

class PackStruct
{
};


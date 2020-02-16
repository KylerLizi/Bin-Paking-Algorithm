#pragma once
#include "PackStruct.h"
#include "vector"
using namespace std;

class binPackingAlgorithm
{
public:

	int curX = 0;//当前坐标x
	int curY = 0;//当前坐标y
	vector<vector<int>> blocks;//存放所有的矩形大小

	//重复添加一定数量的同一矩形
	void AddBlocks(int width, int height, int num);

	//处理二叉树
	BlockTree* CreateNode(int x, int y, int w, int h);
/*	BlockTree * CopyNodeValue(BlockTree * node);//复制非引用时*/

	//处理矩形节点
	void SplitNode(BlockTree* targetNode, BlockTree* tempNode);//以二叉树的形式拆分Target矩形为三部分
	BlockTree* GrowNode(BlockTree* block);//根据规则扩充矩形
	BlockTree* GrowRight(BlockTree* block);
	BlockTree* GrowDown(BlockTree* block);
	void Fit();//遍历所有矩形
	BlockTree* FindNode(BlockTree* leafNode, int fitW, int fitH);//为矩形寻找合适的位置

	//处理叶子链表
	void InsertListNode(BlockTree * deletePos, BlockTree* insertLeft, BlockTree* insertRight);
	void DeleteListNode(BlockTree* node);


	//排序算法
	void SortByWidth();
	void SortByHeight();
	void SortByArea();//按照面积最大排序
	void SortByMaxside();//取出宽与高中的最大边，进行比较

	//打印所有矩形与二叉树
	void PrintBlocks();
	void PrintTree(BlockTree * parent, BlockTree * node, string & prefix);\
};


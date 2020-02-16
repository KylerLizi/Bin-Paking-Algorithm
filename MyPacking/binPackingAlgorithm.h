/******************************************************************************

This is a very simple binary tree based bin packing algorithm that is initialized
with a fixed width and height and will fit each block into the first node where
it fits and then split that node into 2 parts (down and right) to track the
remaining whitespace.

Best results occur when the input blocks are sorted by width.
TODO:or even better when sorted by max(width,height).

******************************************************************************/
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

	void AddBlocks(int width, int height, int num);//重复添加一定数量的同一矩形

	BlockTree* CreateNode(int x, int y, int w, int h);//创建一个矩形节点
	BlockTree* SplitNode(BlockTree* targetNode, BlockTree* tempNode);//以二叉树的形式拆分当前矩形为三部分
	BlockTree* GrowNode(BlockTree* block);//根据规则扩充矩形
	BlockTree* GrowRight(BlockTree* block);
	BlockTree* GrowDown(BlockTree* block);
	void Fit();//遍历所有矩形
	BlockTree* FindNode(BlockTree* node, int fitW, int fitH,int isLeft);//为矩形寻找合适的位置
	void SortByWidth();
	void SortByHeight();
	void SortByArea();//按照面积最大排序
	void SortByMaxside();//取出宽与高中的最大边，进行比较
	void PrintBlocks();
	void PrintTree(BlockTree * parent, BlockTree * node, string & prefix);\
};


#include "binPackingAlgorithm.h"
#include "string"
#include "algorithm"
#include "iostream"

bool cmpByHeight(vector<int> a, vector<int> b)
{
	//优先比较height  从大到小排序
	if (a[1] != b[1])
		return a[1] > b[1];
	else
		return a[0] > b[0];
}

bool cmpByArea(vector<int> a, vector<int> b)
{
	//比较面积
	int areaA = a[0] * a[1];
	int areaB = b[0] * b[1];
	return areaA > areaB;
}

bool cmpByMaxside(vector<int>a, vector<int> b)
{
	return max(a[0], a[1]) > max(b[0], b[1]);
}

void binPackingAlgorithm::AddBlocks(int width, int height, int num)
{
	//重复添加一定数量的同一矩形
	vector<int> loopBlock = { width,height };
	for (int i = 0; i < num; i++)
		blocks.push_back(loopBlock);
}

BlockTree* binPackingAlgorithm::CreateNode(int x,int y,int w,int h)
{
	//初始化一个矩形块
	BlockTree* node = (BlockTree*)malloc(sizeof(BlockTree));
	node->cur = { x,y,w,h };
	node->isUsed = 0;
	node->isLeft = -1;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/*
BlockTree* binPackingAlgorithm::CopyNodeValue(BlockTree* node)
{
	if (node == NULL)
		return NULL;

	BlockTree* copyNode = CreateNode(node->cur.x, node->cur.y,node->cur.w, node->cur.h);
	copyNode->isLeft = node->isLeft;
	copyNode->isUsed = node->isUsed;
	copyNode->left = node->left;
	copyNode->right = node->right;
	return copyNode;
}*/

void binPackingAlgorithm::SplitNode(BlockTree* targetNode, BlockTree* tempNode)
{
	//将一个大矩形(targetNode)划分为1个已用的(tempNode)和2个未用的矩形
	//------------------------------------------
	BlockTree* left = CreateNode(targetNode->cur.x + tempNode->cur.w, targetNode->cur.y, 
		targetNode->cur.w - tempNode->cur.w, tempNode->cur.h);
	left->isLeft = 1;
	BlockTree* right;

	//分割的左右孩子若宽或高为0，则为NULL
	if (targetNode->isLeft == 1 && targetNode->cur.h == tempNode->cur.h)
	{
		right = NULL;
	}
	else
	{
		right = CreateNode(targetNode->cur.x, targetNode->cur.y + tempNode->cur.h, 
			targetNode->cur.w, targetNode->cur.h - tempNode->cur.h);
		right->isLeft = 0;
		if (right->cur.w == 0 || right->cur.h == 0)
			right = NULL;
	}
	//长度为0是无效空矩形
	if (left->cur.w == 0 || left->cur.h == 0)
		left = NULL;

	//更新叶子链表,去掉已用空间的节点，加入它的两个未使用的孩子节点
	InsertListNode(targetNode, left, right);

	targetNode->cur.w = tempNode->cur.w;
	targetNode->cur.h = tempNode->cur.h;
	targetNode->isUsed = 1;//标记已被使用
	targetNode->left = left;
	targetNode->right = right;
}

BlockTree* binPackingAlgorithm::GrowNode(BlockTree* block)
{
	int width = block->cur.w;
	int height = block->cur.h;
	//若矩形块比框宽，我们就不能支持矩形框向下生长
	bool canGrowDown = (width <= g_maxW);
	bool canGrowRight = (height <= g_maxH);

	//为保持近似正方形 特别高的放在右侧 特别宽的放下下面
	bool shouldGrownRight = canGrowRight && (height >= (width + g_maxW));
	bool shouldGrownDown = canGrowDown && (width >= (height + g_maxH));

	if (shouldGrownRight)
		return GrowRight(block);
	else if (shouldGrownDown)
		return GrowDown(block);
	else if(canGrowRight && g_maxH>=g_maxW)
		return GrowRight(block);
	else if (canGrowDown && g_maxH <= g_maxW)
		return GrowDown(block);
	else if (canGrowDown)
		return GrowDown(block);
	else if (canGrowRight)
		return GrowRight(block);
	else
		return NULL;
}

BlockTree* binPackingAlgorithm::GrowRight(BlockTree* block)
{
	int width = block->cur.w;
	int height = block->cur.h;
	//扩大框的最大宽度
	g_maxW += width;

	BlockTree* growNode = CreateNode(0,0,width, g_maxH);

	//寻找到矩形框的最右侧添加要扩容的节点
	BlockTree* rightmost = g_root;
	for (; rightmost->left != NULL; rightmost = rightmost->left);
	growNode->cur.x = rightmost->cur.x + rightmost->cur.w;
	growNode->cur.y = 0;
	growNode->isLeft = 1;
	rightmost->left = growNode;

	//新增叶子链表
	BlockTree* leaf = g_leaf_head;
	while (leaf->right != NULL)
		leaf = leaf->right;
	leaf->right = growNode;

	BlockTree* targetNode;
	if (targetNode = FindNode(g_leaf_head, width, height))
	{
		//tempNode->cur.y = targetNode->cur.y;
		//tempNode->cur.x = targetNode->cur.x;
		SplitNode(targetNode, block);//放入当前矩形，并拆分该空矩形
	}
	return targetNode;
}

BlockTree* binPackingAlgorithm::GrowDown(BlockTree* block)
{
	int width = block->cur.w;
	int height = block->cur.h;
	//扩大框的最大高度
	g_maxH += height;

	BlockTree* growNode = CreateNode(0,0,g_maxW, height);

	//寻找到矩形框的最下侧添加要扩容的节点
	BlockTree* downMost = g_root;
	for (; downMost->right != NULL; downMost = downMost->right);
	growNode->cur.x = 0;
	growNode->cur.y = downMost->cur.y + downMost->cur.h;
	growNode->isLeft = 0;
	downMost->right = growNode;
	
	//新增叶子链表
	BlockTree* leaf = g_leaf_head;
	while (leaf->right != NULL)
		leaf = leaf->right;
	leaf->right = growNode;

	BlockTree* targetNode;
	if (targetNode = FindNode(g_leaf_head, width, height))
		SplitNode(targetNode, block);//放入当前矩形，并拆分该空矩形
	return targetNode;
}

void binPackingAlgorithm::Fit()
{
	//创建根节点
	g_maxW = blocks[0][0];
	g_maxH = blocks[0][1];
	g_root = CreateNode(0, 0, blocks[0][0], blocks[0][1]);//创建第一个最大的矩形
	g_root->isUsed = 1;
	//创建叶子链表头节点
	g_leaf_head = CreateNode(0, 0, 0, 0);

	//对剩余的矩形 逐个添加到排版空间中
	for (int i = 1; i < blocks.size(); i++)
	{
		BlockTree* targetNode;
		BlockTree* tempNode = CreateNode(curX, curY, blocks[i][0], blocks[i][1]);
		
		//查找判断矩形向右生长还是向下扩大
		if (targetNode = FindNode(g_leaf_head, blocks[i][0], blocks[i][1]))
		{
			SplitNode(targetNode,tempNode);//放入当前矩形，并拆分该空矩形
		}
		else
		{
			BlockTree* res = GrowNode(tempNode);
			if (res == NULL)
				cout << endl << "Grow node failed!" << endl << endl;
		}
	}
	
}

//叶子链表查找速度快
BlockTree* binPackingAlgorithm::FindNode(BlockTree* leafNode, int blockW, int blockH)
{
	leafNode = leafNode->right;
	//查找能放进去该矩形的空矩形
	while (leafNode != NULL)
	{
		if (leafNode->cur.w >= blockW && leafNode->cur.h >= blockH)
			return leafNode;
		leafNode = leafNode->right;
	}
	return NULL;
}

void binPackingAlgorithm::InsertListNode(BlockTree * deletePos,BlockTree* insertLeft, BlockTree* insertRight)
{
	if (deletePos == NULL)
		return;
	
	BlockTree* leaf = g_leaf_head->right;//删除点
	BlockTree* preLeaf = g_leaf_head;//删除点的前一个节点
	while (leaf != NULL && leaf != deletePos)
	{
		leaf = leaf->right;
		preLeaf = preLeaf->right;
	}
	if (leaf == deletePos)
	{//插入
		if (insertLeft != NULL && !insertLeft->isUsed)
		{
			insertLeft->right = leaf;
			preLeaf->right = insertLeft;
		}
		if (insertRight != NULL && !insertRight->isUsed)
		{
			insertRight->right = leaf->right;
			leaf->right = insertRight;
		}
		DeleteListNode(leaf);
	}
}

void binPackingAlgorithm::DeleteListNode(BlockTree * deleteNode)
{
	//preNode--insertLeft(可能有)--node(删除)--insertRight(可能有)
	BlockTree* leaf = g_leaf_head->right;//删除点
	BlockTree* preLeaf = g_leaf_head;//删除点的前一个节点
	while (leaf != NULL && leaf != deleteNode)
	{
		leaf = leaf->right;
		preLeaf = preLeaf->right;
	}
	if (leaf == deleteNode)
	{
		preLeaf->right = leaf->right;
	}
}

void binPackingAlgorithm::SortByWidth()
{
	sort(blocks.begin(), blocks.end(), greater<vector<int>>());
}

void binPackingAlgorithm::SortByHeight()
{
	sort(blocks.begin(), blocks.end(), cmpByHeight);
}

void binPackingAlgorithm::SortByArea()
{
	sort(blocks.begin(), blocks.end(), cmpByArea);
}

void binPackingAlgorithm::SortByMaxside()
{
	sort(blocks.begin(), blocks.end(), cmpByMaxside);
}

void binPackingAlgorithm::PrintBlocks()
{
	for (int i = 0; i < blocks.size(); i++)
		cout << blocks[i][0] << "," << blocks[i][1] << endl;
}

void binPackingAlgorithm::PrintTree(BlockTree* parent,BlockTree* node,string &prefix) 
{
	prefix += "|";
	if (node)
	{
		if (node == parent)
			prefix.pop_back();
		cout << prefix << "--" << node->isUsed << ",[" << node->cur.x << "," << node->cur.y << "," << node->cur.w << "," << node->cur.h << "]" << endl;
		if (node == parent->right)
			if(prefix.compare(""))
				prefix.pop_back();
		if (node->isUsed)
		{
			string addStr = prefix + "  ";
			PrintTree(node, node->left, addStr);
			addStr.pop_back();
			PrintTree(node, node->right, addStr);
		}
	}
	else
	{
		if (parent->left || parent->right)//有一个孩子节点不空就打印，用来区分左右孩子
			cout << prefix << "--" << "NULL" << endl;
	}
}
#include "BinaryTree.h"

// ------------------------------------------
int DepthBT(BTREE BT)
{
	int leftHeight, rightHeight;
	if (BT == NULL)
		return 0;
	leftHeight = DepthBT(BT->pLeft);
	rightHeight = DepthBT(BT->pRight);
	return ((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1;
}
//-------------------------------------------
int LevelBSTNode(BTREE BT, int data)
{
	int depth = 0;
	while (BT != NULL && *(int *)DATA(BT) != data)
	{
		if (data < *(int *)DATA(BT))
			BT = BT->pLeft;
		else
			BT = BT->pRight;
		depth++;
	}
	if (BT == NULL)
		depth = -1;
	return depth;
}
//-------------------------------------------
int LevelBTNode(BTREE BT, int data)
{
	int depth = -1;
	if (BT == NULL)
		return -1;
	if (*(int *)BT->pData == data || (depth = LevelBTNode(BT->pLeft, data)) >= 0 || (depth = LevelBTNode(BT->pRight, data)) >= 0)
		return (depth + 1);
	return depth;
}
//-------------------------------------------
int NoBTLeaves(BTREE BT)
{
	int count = 0;
	if (BT == NULL)
		return count;
	count += NoBTLeaves(BT->pLeft);
	if (BT->pLeft == NULL && BT->pRight == NULL)
		count++;
	count += NoBTLeaves(BT->pRight);
	return count;
}
//-------------------------------------------
int NoBTNodes(BTREE BT)
{
	int count = 0;
	if (BT == NULL)
		return count;
	count++;
	count += NoBTNodes(BT->pLeft);
	count += NoBTNodes(BT->pRight);
	return count;
}
//-------------------------------------------
BTREE findAgeBTNode(BTREE BT, int age)
{
	if (!emptyBTree(BT))
	{
		while (BT != NULL)
		{
			if (age == *(int *)BT->pData)
				return BT;
			else if (age < *(int *)BT->pData)
				BT = BT->pLeft;
			else
				BT = BT->pRight;
		}
	}
	return NULL;
}
//-------------------------------------------
void postOrderTreeWalk(BTREE BT)
{
	if (!emptyBTree(BT))
	{
		postOrderTreeWalk(BT->pLeft);
		postOrderTreeWalk(BT->pRight);
		printf("%d, ", *(int *)BT->pData);
	}
}
//-------------------------------------------
void preOrderTreeWalk(BTREE BT)
{
	if (!emptyBTree(BT))
	{
		printf("%d, ", *(int *)BT->pData);
		preOrderTreeWalk(BT->pLeft);
		preOrderTreeWalk(BT->pRight);
	}
}
//-------------------------------------------
void inOrderTreeWalk(BTREE BT)
{
	if (!emptyBTree(BT))
	{
		inOrderTreeWalk(BT->pLeft);
		printf("%d, ", *(int *)BT->pData);
		inOrderTreeWalk(BT->pRight);
	}
}
//-------------------------------------------
STATUS initBTree(BTREE *pBT)
{
	*pBT = NULL;
	return OK;
}
//-------------------------------------------
bool emptyBTree(BTREE BT)
{
	return (BT == NULL);
}
//-------------------------------------------
bool isLeaf(BTREE_NODE *pBT)
{
	return ((LEFT(pBT) == NULL) && (RIGHT(pBT) == NULL));
}
//-------------------------------------------
STATUS createNewBTNode(BTREE_NODE **pNew, void *pData)
{
	BTREE_NODE *pTemp;
	if ((pTemp = (BTREE_NODE *)malloc(sizeof(BTREE_NODE))) == NULL)
		return ERROR;
	*pNew = pTemp;
	DATA(pTemp) = pData;
	LEFT(pTemp) = NULL;
	RIGHT(pTemp) = NULL;
	return OK;
}
//-------------------------------------------
//-------------------------------------------
// This function is not for use with any BT
// It can only be used with INT BTs
//-------------------------------------------
void printIntBTree(BTREE BT)
{
	if (emptyBTree(BT))
		return;
	printIntBTree(LEFT(BT));
	printf("%d, ", *(int *)DATA(BT));
	printIntBTree(RIGHT(BT));
	return;
}
//-------------------------------------------
// This function is not for use with any BST
// It can only be used with INT BSTs
//-------------------------------------------
STATUS insertIntBST(BTREE *pBT, void *pData)
{
	if (emptyBTree(*pBT))
	{
		BTREE_NODE *pNew;
		if (createNewBTNode(&pNew, pData) == ERROR)
			return ERROR;
		*pBT = pNew;
		return OK;
	}
	else if (*(int *)(pData) < *(int *)(DATA(*pBT)))
		insertIntBST(&(LEFT(*pBT)), pData);
	else
		insertIntBST(&(RIGHT(*pBT)), pData);
	return OK;
}
//-------------------------------------------
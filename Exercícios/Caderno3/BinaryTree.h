#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DATA(node) ((node)->pData)
#define LEFT(node) ((node)->pLeft)
#define RIGHT(node) ((node)->pRight)
#define EMPTY NULL
#define NO_LINK NULL

typedef enum _STATUS { OK, ERROR } STATUS;

typedef struct _BTREE_NODE 
{
	void* pData;
	struct _BTREE_NODE* pLeft;
	struct _BTREE_NODE* pRight;
} BTREE_NODE;

typedef BTREE_NODE* BTREE;

//----BASE-----------------------------------
STATUS initBTree(BTREE*);
bool emptyBTree(BTREE);
bool isLeaf(BTREE_NODE*);
STATUS createNewBTNode(BTREE_NODE**, void*);
//funcoes novas
int DepthBT(BTREE);
int LevelBSTNode(BTREE, int);
int LevelBTNode(BTREE, int);
int NoBTLeaves(BTREE);
int NoBTNodes(BTREE);
BTREE findAgeBTNode(BTREE, int);
void inOrderTreeWalk(BTREE);
void preOrderTreeWalk(BTREE);
void postOrderTreeWalk(BTREE);
// especificas duma arvore de inteiros
void printIntBTree(BTREE);
STATUS insertIntBST(BTREE*, void*);
// impressao
#pragma once

#include "Player.h"
#include <stdbool.h>

typedef struct _BTREE_NODE
{
	void* data;
	struct _BTREE_NODE* left;
	struct _BTREE_NODE* right;
} BTREE_NODE;

typedef BTREE_NODE* BTREE;
typedef enum _BTREE_LOCATION { BTREE_LEFT, BTREE_RIGHT } BTREE_LOCATION;
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;

#define DATA(node) ((node)->data)
#define LEFT(node) ((node)->left)
#define RIGHT(node) ((node)->right)
#define EMPTY NULL
#define NO_LINK NULL

STATUS ReadPlayersFromFile(void**, const char*);
BTREE_NODE* NewBtreeNode(void* data);
BTREE_NODE* InitNode(void*, BTREE_NODE*, BTREE_NODE*);
BTREE_NODE* CreateBtree(void**, int, int);
void BtreeFree(BTREE);
void ShowPlayers(BTREE);
int NoEliminatorias(BTREE);
void ShowJogos(BTREE);
void ShowVencedor(BTREE);
void ShowJogosVencedor(BTREE);

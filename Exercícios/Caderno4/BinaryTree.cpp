#include "BinaryTree.h"

// Especifico do jogador
void ShowVencedor(BTREE BT)
{
	if (BT == NULL)
		return;
	printf("Vencedor: %s\n", ((PLAYER*)BT->data)->name);
	ShowJogosVencedor(BT);
}
//////////////////////////////
void ShowJogosVencedor(BTREE BT)
{
	if (BT != NULL)
	{
		if (BT->left != NULL && BT->right != NULL)
		{
			printf("%s sets:%d VS. %s sets:%d\n", ((PLAYER*)BT->left->data)->name, ((PLAYER*)BT->left->data)->sets,
				((PLAYER*)BT->right->data)->name, ((PLAYER*)BT->right->data)->sets);
			if (strcmp(((PLAYER*)BT->data)->name, ((PLAYER*)BT->left->data)->name) == 0)
				ShowJogosVencedor(BT->left);
			else if (strcmp(((PLAYER*)BT->data)->name, ((PLAYER*)BT->right->data)->name) == 0)
				ShowJogosVencedor(BT->right);
		}
	}
}
//////////////////////////////
void ShowJogos(BTREE BT)
{
	if (BT == NULL)
		return;
	if (BT->left != NULL && BT->right != NULL)
	{
		printf("%s sets:%d VS. %s sets:%d\n", ((PLAYER*)BT->left->data)->name, ((PLAYER*)BT->left->data)->sets,
			((PLAYER*)BT->right->data)->name, ((PLAYER*)BT->right->data)->sets);
		ShowJogos(BT->left);
		ShowJogos(BT->right);
	}
}
//////////////////////////////
int NoEliminatorias(BTREE BT)
{
	if (BT == NULL)
		return 0;
	if (BT->left != NULL && BT->right != NULL)
		return (1 + NoEliminatorias(BT->left) + NoEliminatorias(BT->right));
	return 0;
}
/////////////////////////////
void ShowPlayers(BTREE BT)
{
	if (BT == NULL)
		return;
	if (BT->left == NULL && BT->right == NULL)
	{
		printf("%s\n", ((PLAYER*)BT->data)->name);
	}
	ShowPlayers(BT->left);
	ShowPlayers(BT->right);
}
////////////////////////////
STATUS ReadPlayersFromFile(void** players, const char* file_name)
{
	FILE* fp;
	int j, i = 0;
	void* ptr_data;
	if ((fp = fopen(file_name, "r")) != NULL)
	{
		while (!feof(fp))
		{
			if ((ptr_data = malloc(sizeof(PLAYER))) != NULL)
			{
				fscanf(fp, "%[^;];", ((PLAYER*)ptr_data)->name);
				fscanf(fp, "%d\n", &(((PLAYER*)ptr_data)->sets));
				players[i] = ptr_data;
				i++;
			}
			else
			{
				for (j = i; j >= 0; j--)
					free(players[j]);
				return(ERROR);
			}
		}
		fclose(fp);
		return(OK);
	}
	else
		return(ERROR);
}

BTREE_NODE* NewBtreeNode(void* data)
{
	BTREE_NODE* tmp_pt;
	if ((tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL)
	{
		DATA(tmp_pt) = data;
		LEFT(tmp_pt) = RIGHT(tmp_pt) = NULL;
	}
	return tmp_pt;
}

BTREE_NODE* InitNode(void* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2)
{
	BTREE_NODE* tmp_pt = NULL;
	tmp_pt = NewBtreeNode(ptr_data);
	LEFT(tmp_pt) = node1;
	RIGHT(tmp_pt) = node2;
	return(tmp_pt);
}

BTREE_NODE* CreateBtree(void** v, int i, int size)
{
	if (i >= size)
		return(NULL);
	else
		return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size)));
}

void BtreeFree(BTREE btree)
{
	if (btree != NULL)
	{
		BtreeFree(LEFT(btree));
		BtreeFree(RIGHT(btree));
		free(DATA(btree));
		free(btree);
	}
}
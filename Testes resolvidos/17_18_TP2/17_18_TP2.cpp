#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _DEPT {
	char desig[20];
	float ganhos, despesas;
	int n_pessoas;
}DEPT;

typedef struct _BTREE_NODE {
	void* data;
	struct _BTREE_NODE* left;
	struct _BTREE_NODE* right;
} BTREE_NODE;

#define DATA(node) ((node)->data)
#define LEFT(node) ((node)->left)
#define RIGHT(node) ((node)->right)

typedef BTREE_NODE* BTREE;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;

int main(int argc, char* argv[])
{
	BTREE btree;
	void* depts[15];
	char file_name[20];
	printf("Nome do ficheiro: ");
	scanf("%s", file_name);
	if (ReadFile(depts, file_name)) {
		btree = CreateBtree(depts, 0, 15);
		BtreeFree(btree);
	}
	else printf("ERRO na leitura do ficheiro\n");
	return 1;
}

// Exercício 1
float Lucros(BTREE BT)
{
	float total = 0;
	if (BT == NULL)
		return total;
	total += Lucros(BT->left);
	total += ((DEPT*)BT->data)->ganhos - ((DEPT*)BT->data)->despesas;
	total += Lucros(BT->right);
	return total;
}

// Exercício 2
STATUS ShowMax(BTREE BT)
{
	int max;
	DEPT* aux;
	max = MaxPessoas(BT);
	if (FindMax(BT, max))
		return OK;
}
int MaxPessoas(BTREE BT)
{
	int max, lmax, rmax;
	if (BT == NULL)
		return -1;
	lmax = MaxPessoas(BT->left);
	max = ((DEPT*)BT->data)->n_pessoas;
	rmax = MaxPessoas(BT->right);
	if (lmax > max)
		max = lmax;
	if (rmax > max)
		max = rmax;
	return max;
}
bool FindMax(BTREE BT, int max)
{
	DEPT* aux = NULL;
	if (BT == NULL)
		return false;
	aux = (DEPT*)BT->data;
	if (aux->n_pessoas == max)
	{
		printf("\nDesignacao: %s", aux->desig);
		printf("\nGanhos: %f", aux->ganhos);
		printf("\nDespesas: %f", aux->despesas);
		printf("\nNo pesssoas: %d", aux->n_pessoas);
		return true;
	}
	if (FindMax(BT->left, max))
		return true;
	return FindMax(BT->right, max);
}

// Exercício 3
void DelSubDep(BTREE BT)
{
	char des[20];
	printf("Designacao: ");
	scanf(" %[^\n]", des);
	FindDep(BT, des);
}
bool FindDep(BTREE BT, char* des)
{
	int n = 0;
	DEPT* aux = NULL;
	if (BT == NULL)
		return false;
	aux = (DEPT*)BT->data;
	if (strcmp(aux->desig, des) == 0)
	{
		n += DelRec(BT->left);
		free(BT->left);
		BT->left = NULL;
		n += DelRec(BT->right);
		free(BT->right);
		BT->right = NULL;
		aux->n_pessoas = n;
		return true;
	}
	if (FindDep(BT->left, des))
		return true;
	return FindDep(BT->right, des);
}
int DelRec(BTREE BT)
{
	int n = 0;
	if (BT == NULL)
		return n;
	n += DelRec(BT->left);
	n += DelRec(BT->right);
	free(BT->left);
	BT->left = NULL;
	free(BT->right);
	BT->right = NULL;
	n += ((DEPT*)BT->data)->n_pessoas;
	free(BT->data);
	return n;
}

///////////////////////////////////////////
BTREE_NODE* NewBtreeNode(void* data)
{
	BTREE_NODE* tmp_pt;
	if ((tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL) {
		DATA(tmp_pt) = data;
		LEFT(tmp_pt) = RIGHT(tmp_pt) = NULL;
	}
	return tmp_pt;
}
void BtreeFree(BTREE btree)
{
	if (btree != NULL) {
		BtreeFree(LEFT(btree));
		BtreeFree(RIGHT(btree));
		free(DATA(btree));
		free(btree);
	}
}
BTREE_NODE* InitNode(void* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2)
{
	BTREE_NODE* tmp_pt = NULL;
	tmp_pt = NewBtreeNode(ptr_data);
	LEFT(tmp_pt) = node1;
	RIGHT(tmp_pt) = node2;
	return(tmp_pt);
}
STATUS ReadFile(void** depts, char* file_name)
{
	FILE* fp;
	int j, i = 0;
	void* ptr_data;
	if ((fp = fopen(file_name, "r")) != NULL) {
		while (!feof(fp)) {
			if ((ptr_data = malloc(sizeof(DEPT))) != NULL) {
				fscanf(fp, "%[^;];%d;%f;%f\n", ((DEPT*)ptr_data)->desig, 
					&((DEPT*)ptr_data)->n_pessoas,
					&((DEPT*)ptr_data)->ganhos, 
					&((DEPT*)ptr_data)->despesas);
				depts[i] = ptr_data;
				i++;
			}
			else {
				for (j = i; j >= 0; j--)
					free(depts[j]);
				return(ERROR);
			}
		}
		fclose(fp);
		return(OK);
	}
	else
		return(ERROR);
}
BTREE_NODE* CreateBtree(void** v, int i, int size)
{
	if (i >= size) return(NULL);
	else return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size)));
}
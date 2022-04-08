#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _PERSON {
	char name[50];
	int age;
	BOOLEAN alive;
}PERSON;

typedef struct _BTREE_NODE
{
	void* data;
	struct _BTREE_NODE* left;
	struct _BTREE_NODE* right;
}BTREE_NODE;

#define DATA(node) ((node)->data)
#define LEFT(node) ((node)->left)
#define RIGHT(node) ((node)->right)

typedef BTREE_NODE* BTREE;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;

int main(int argc, char* argv[])
{
	BTREE btree;
	void* persons[15];
	char file_name[20];
	printf("Nome do ficheiro: ");
	scanf("%s", file_name);
	if (ReadFile(persons, file_name))
	{
		btree = CreateBtree(persons, 0, 15);
		BtreeFree(btree);
	}
	else
		printf("ERRO na leitura do ficheiro\n");
	return 1;
}

// Exercício 1
// Desenvolva o código necessário para contar o número de pessoas da árvore que estão vivas (alive = TRUE).
int CountAlive(BTREE BT)
{
	int count = 0;
	if (BT == NULL)
		return count;
	if (((PERSON*)BT->data)->alive == TRUE)
		count++;
	count += CountAlive(BT->left);
	count += CountAlive(BT->right);
	return count;
}

// Exercício 2
// Desenvolva o código necessário para alterar o nome de uma pessoa cujo nome original, e o final, devem ser lidos através do teclado.
bool ChangeName(BTREE BT)
{
	char old_name[50], new_name[50];
	printf("\nNome a mudar: ");
	scanf("%[^\n]", old_name);
	printf("\nNovo nome: ");
	scanf("%[^\n]", new_name);
	return FindName(BT, old_name, new_name);
}

bool FindName(BTREE BT, char* old_name, char* new_name)
{
	if (BT == NULL)
		return false;
	if (strcmp(((PERSON*)BT->data)->name, old_name) == 0)
	{
		strcpy(((PERSON*)BT->data)->name, new_name);
		return true;
	}
	if (FindName(BT->left, old_name, new_name))
		return true;
	return FindName(BT->right, old_name, new_name);
}

// Exercício 3
// Desenvolva o código necessário para acrescentar 2 nós de árvore (filho da esquerda e da direita) à folha mais à direita da árvore. 
// NOTA: os dados dos novos nós devem ser introduzidos através do teclado.
bool AddMostRightChildren(BTREE BT)
{
	PERSON P1, P2;
	if (BT == NULL)
		return false;
	printf("\nNome 1: ");
	scanf(" %[^\n]", P1.name);
	printf("\nIdade 1: ");
	scanf(" %d", &P1.age);
	printf("\n Vivo / Morto (1/0): ");
	scanf(" %d", &P1.alive);
	printf("\nNome 2: ");
	scanf(" %[^\n]", P2.name);
	printf("\nIdade 2: ");
	scanf(" %d", &P2.age);
	printf("\n Vivo / Morto (1/0): ");
	scanf(" %d", &P2.alive);
	while (BT->right != NULL || BT->left != NULL)
	{
		if (BT->right != NULL)
			BT = BT->right;
		else
			BT = BT->left;
	}
	BT->left = NewBtreeNode(&P1);
	BT->right = NewBtreeNode(&P2);
	return true;
}

/////////////////////////////////////////////
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
BTREE_NODE* InitNode(void* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2)
{
	BTREE_NODE* tmp_pt = NULL;
	tmp_pt = NewBtreeNode(ptr_data);
	LEFT(tmp_pt) = node1;
	RIGHT(tmp_pt) = node2;
	return(tmp_pt);
}
STATUS ReadFile(void** persons, char* file_name)
{
	FILE* fp;
	int aux, j, i = 0;
	void* ptr_data;
	if ((fp = fopen(file_name, "r")) != NULL) 
	{
		while (!feof(fp))
		{
			if ((ptr_data = malloc(sizeof(PERSON))) != NULL)
			{
				fscanf(fp, "%[^;];%d;%d\n", ((PERSON*)ptr_data)->name, 
					&((PERSON*)ptr_data)->age, &aux); 
				if (aux) 
					((PERSON*)ptr_data)->alive = TRUE;
				else 
					((PERSON*)ptr_data)->alive = FALSE;
				persons[i] = ptr_data;
				i++;
			}
			else 
			{
				for (j = i; j >= 0; j--)
					free(persons[j]);
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
	if (i >= size) 
		return(NULL);
	else 
		return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size)));
}
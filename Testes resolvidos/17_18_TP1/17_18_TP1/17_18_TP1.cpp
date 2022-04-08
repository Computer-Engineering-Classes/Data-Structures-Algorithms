#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DATA(node) ((node)->data)
#define NEXT(node) ((node)->next)
typedef enum _STATUS { ERROR, OK } STATUS;
typedef enum _BOOLEAN { FALSE, TRUE } BOOLEAN;

#define MAX_NOME 20

typedef struct _PLAYER 
{
	char nome[MAX_NOME];
	char clube[MAX_NOME];
	int posicao;
	BOOLEAN titular;
} PLAYER;

typedef struct _LIST_NODE
{
	void* data;
	struct _LIST_NODE* next;
} LIST_NODE;

typedef LIST_NODE* LIST;

LIST_NODE* NewNode(void*);
LIST_NODE* InsertIni(LIST*, void*);
void FreeList(LIST* list);

STATUS ReadFile(LIST*, const char*);
void AddPlayer(LIST*);
void ShowPlayerTitular(LIST list);
void SwitchTitular(LIST list);
LIST_NODE* FindPlayer(LIST list, char* nome);

int main(int argc, char* argv[])
{
	LIST list = NULL;
	PLAYER player;
	/*if (!ReadFile(&list, "selecao.txt"))
		return 0;*/
	AddPlayer(&list);
	AddPlayer(&list);
	ShowPlayerTitular(list);
	SwitchTitular(list);
	ShowPlayerTitular(list);
	FreeList(&list);
	return 1;
}

void SwitchTitular(LIST list)
{
	PLAYER* tmp;
	LIST_NODE* p1, * p2;
	char* n1, * n2;
	n1 = (char*)malloc(MAX_NOME * sizeof(char) + 1);
	n2 = (char*)malloc(MAX_NOME * sizeof(char) + 1);
	//n1[MAX_NOME] = '\0';
	//n2[MAX_NOME] = '\0';
	printf("\nNome do jogador 1: ");
	scanf(" %[^\n]", n1);
	printf("\nNome do jogador 2: ");
	scanf(" %[^\n]", n2);
	p1 = FindPlayer(list, n1);
	p2 = FindPlayer(list, n2);
	tmp = (PLAYER*)DATA(p1);
	DATA(p1) = (PLAYER*)DATA(p2);
	DATA(p2) = tmp;
	free(n1);
	free(n2);
}

LIST_NODE* FindPlayer(LIST list, char* nome)
{
	while (list != NULL)
	{
		if (strcmp(((PLAYER*)DATA(list))->nome, nome) == 0)
			return list;
		list = NEXT(list);
	}
	return NULL;
}

void ShowPlayerTitular(LIST list)
{
	PLAYER* tmp;
	printf("\nPlayers titulares:\n");
	while (list != NULL)
	{
		tmp = (PLAYER*)DATA(list);
		if (tmp->titular == TRUE)
		{
			printf("\nNome: %s\n", tmp->nome);
			printf("\nClube: %s\n", tmp->clube);
			printf("\nPosicao: %d", tmp->posicao);
		}
		list = NEXT(list);
	}
}

void AddPlayer(LIST* list)
{
	int titular;
	PLAYER* tmp;
	tmp = (PLAYER*)malloc(sizeof(PLAYER));
	printf("\nNovo jogador:\n");
	printf("\nNome: ");
	scanf(" %[^\n]", tmp->nome);
	printf("\nClube: ");
	scanf(" %[^\n]", tmp->clube);
	printf("\nPosicao: ");
	scanf(" %d", &tmp->posicao);
	do
	{
		printf("Titular? (1 = Sim, 0 = Não): ");
		scanf("%d", &titular);
	} while (!(titular == 0 || titular == 1));
	tmp->titular = (BOOLEAN)titular;
	InsertIni(list, tmp);
}

STATUS ReadFile(LIST* list, const char* name_file)
{
	FILE* fp;
	PLAYER player, * ptr;
	int aux;
	if ((fp = fopen(name_file, "r")) != NULL)
	{
		while (!feof(fp)) //while(feof(fp) == 0) 
		{
			fscanf(fp, "%[^;]; %[^;];%f;%d\n", player.nome, player.clube, &player.posicao, &aux);
			if (((ptr = (PLAYER*)malloc(sizeof(PLAYER))) != NULL) && (InsertIni(list, ptr) != NULL))
			{
				strcpy(ptr->nome, player.nome);
				strcpy(ptr->clube, player.clube);
				ptr->posicao = player.posicao;
				if (aux) ptr->titular = TRUE;
				else ptr->titular = FALSE;
			}
			else
				return ERROR;
		}
		fclose(fp);
		return OK;
	}
	else
		return ERROR;
}

LIST_NODE* NewNode(void* data)
{
	LIST_NODE* new_node;
	if ((new_node = (LIST_NODE*)malloc(sizeof(LIST_NODE))) != NULL) {
		DATA(new_node) = data;
		NEXT(new_node) = NULL;
	}
	return(new_node);
}
LIST_NODE* InsertIni(LIST* list, void* data)
{
	LIST_NODE* new_node;
	if ((new_node = NewNode(data)) != NULL) {
		NEXT(new_node) = *list;
		*list = new_node;
	}
	return(new_node);
}

void FreeList(LIST* list)
{
	LIST tmp = *list;
	LIST aux = NEXT(tmp);
	if (*list == NULL)
		return;
	while (aux != NULL)
	{
		free(DATA(tmp));
		free(tmp);
		tmp = aux;
		aux = NEXT(tmp);
	}
	free(DATA(tmp));
	free(tmp);
}

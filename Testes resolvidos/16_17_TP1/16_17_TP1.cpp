#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DATA(node) ((node)->data)
#define NEXT(node) ((node)->next)

typedef enum _STATUS { ERROR, OK } STATUS;

#define MAX_NOME 20

typedef struct _SMARTPHONE {
	char marca[MAX_NOME];
	char modelo[MAX_NOME];
	float preco;
	int stock;
} SMARTPHONE;

typedef struct _LIST_NODE
{
	void* data;
	struct _LIST_NODE* next;
} LIST_NODE;

typedef LIST_NODE* LIST;

LIST_NODE* NewNode(void*);
LIST_NODE* InsertIni(LIST*, void*);
STATUS ReadFile(LIST*, const char*);
void DelStockZero(LIST* list);
void ShowLista(LIST);

int main(int argc, char* argv[])
{
	LIST list = NULL;
	SMARTPHONE phone;
	ReadFile(&list, "smartphones.txt");
	ShowLista(list);
	DelStockZero(&list);
	printf("\n----------------\n");
	ShowLista(list);
	//FreeList(&list);
	return 1;
}

void ShowLista(LIST L)
{
	SMARTPHONE* aux;
	while (L != NULL)
	{
		aux = (SMARTPHONE*)DATA(L);
		printf("\n%s | %s | %lf | %d\n", aux->marca, aux->modelo, aux->preco, aux->stock);
		L = NEXT(L);
	}
}

void DelStockZero(LIST* list)
{
	LIST prev = NULL, tmp = NULL;
	LIST_NODE* aux = NULL;
	if (*list != NULL)
	{
		while (((SMARTPHONE*)(*list)->data)->stock == 0)
		{
			aux = (*list)->next;
			free((*list)->data);
			free(*list);
			*list = aux;
		}
		tmp = *list;
		prev = tmp;
		tmp = tmp->next;
		while (tmp != NULL)
		{
			if (((SMARTPHONE*)(tmp->data))->stock == 0)
			{
				prev->next = tmp->next;
				free(tmp->data);
				free(tmp);
				tmp = prev;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

STATUS ReadFile(LIST* list, const char* name_file)
{
	FILE* fp;
	SMARTPHONE phone, * ptr;
	if ((fp = fopen(name_file, "r")) != NULL) {
		while (!feof(fp)) /*while(feof(fp) == 0) */{
			fscanf(fp, "%[^;];%[^;];%f;%d\n", phone.marca, phone.modelo, &phone.preco, &phone.stock);
		if (((ptr = (SMARTPHONE*)malloc(sizeof(SMARTPHONE))) != NULL) && (InsertIni(list, ptr) != NULL)) 
		{
			strcpy(ptr->marca, phone.marca);
			strcpy(ptr->modelo, phone.modelo);
			ptr->preco = phone.preco;
			ptr->stock = phone.stock;
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
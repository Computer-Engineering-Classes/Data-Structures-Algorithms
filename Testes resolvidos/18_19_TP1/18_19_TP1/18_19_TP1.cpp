#define MAX_NOME 20

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#include "List.h"
#include <stdio.h>
#include <string.h>

typedef struct _FUNC 
{
	char nome[MAX_NOME], dept[MAX_NOME];
	float ordenado;
	BOOLEAN do_quadro;
} FUNC;

STATUS ReadFile(LIST*, const char*);
void ShowOrdenadoTotal(LIST list);
void ChangeToQuadro(LIST list);
void DeleteNaoQuadro(LIST* list);
void ShowFunc(LIST list);

int main(int argc, char* argv[])
{
	LIST list = NULL;
	FUNC func;
	if (!ReadFile(&list, "funcionarios.txt"))
		return 0;
	ShowOrdenadoTotal(list);
	ShowFunc(list);
	ChangeToQuadro(list);
	DeleteNaoQuadro(&list);
	ShowFunc(list);
	FreeList(&list);
	return 1;
}

void DeleteNaoQuadro(LIST* list)
{
	LIST_NODE* aux;
	LIST tmp;
	if (list != NULL)
	{
		while (((FUNC*)DATA(*list))->do_quadro == FALSE)
			RemoveFirstNode(list);
	}
	tmp = *list;
	while (tmp != NULL)
	{
		if (((FUNC*)DATA(NEXT(tmp)))->do_quadro == FALSE)
		{
			aux = NEXT(NEXT(tmp));
			free(DATA(NEXT(tmp)));
			free(NEXT(tmp));
			NEXT(tmp) = aux;
		}
		tmp = NEXT(tmp);
	}
}

void ChangeToQuadro(LIST list)
{
	FUNC* tmp;
	char* aux;
	aux = (char*)malloc(MAX_NOME * sizeof(char));
	printf("\nNome do funcionario que deseja passar para o quadro: ");
	scanf(" %[^\n]", aux);
	while (list != NULL)
	{
		tmp = (FUNC*)DATA(list);
		if (strcmp(tmp->nome, aux) == 0)
		{
			switch (tmp->do_quadro)
			{
			case TRUE:
				printf("\nO funcionario %s ja se encontra no quadro.\n", aux);
				break;
			case FALSE:
				tmp->do_quadro = TRUE;
				printf("\nO funcionario %s faz agora parte do quadro.\n", aux);
				break;
			}
			free(aux);
			return;
		}
		list = NEXT(list);
	}
	printf("\nO funcionario %s nao faz parte da lista.\n", aux);
	free(aux);
}

void ShowOrdenadoTotal(LIST list)
{
	float total = 0;
	while (list != NULL)
	{
		total += ((FUNC*)DATA(list))->ordenado;
		list = NEXT(list);
	}
	printf("\nTotal dos ordenados pagos aos funcionarios: %f\n", total);
}

void ShowFunc(LIST list)
{
	FUNC aux;
	while (list != NULL)
	{
		aux = *((FUNC*)DATA(list));
		printf("\nFuncionario:\n");
		printf("\n\tNome: %s\n", aux.nome);
		printf("\n\tDepartamento: %s\n", aux.dept);
		printf("\n\tOrdenado: %f\n", aux.ordenado);
		printf("\n\tQuadro? %d\n", aux.do_quadro);
		list = NEXT(list);
	}
}
STATUS ReadFile(LIST* list, const char* name_file)
{
	FILE* fp;
	FUNC func, * ptr;
	int aux;
	if ((fp = fopen(name_file, "r")) != NULL)
	{
		while (!feof(fp)) //while(feof(fp) == 0)
		{
			fscanf(fp, "%[^;]; %[^;];%f;%d\n", func.nome, func.dept, &func.ordenado, &aux);
			if (((ptr = (FUNC*)malloc(sizeof(FUNC))) != NULL) && (InsertIni(list, ptr) != NULL))
			{
				strcpy(ptr->nome, func.nome);
				strcpy(ptr->dept, func.dept);
				ptr->ordenado = func.ordenado;
				if (aux) ptr->do_quadro = TRUE;
				else ptr->do_quadro = FALSE;
			}
			else return ERROR;
		}
		fclose(fp);
		return OK;
	}
	else return ERROR;
}
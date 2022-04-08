#include "Smartphone.h"

void ShowLista(LIST L)
{
	SMARTPHONE* aux;
	while (L != NULL)
	{
		aux = (SMARTPHONE*)DATA(L);
		printf("\n%s | %s | %lf | %d\n", aux->marca, aux->modelo, aux->preco, aux->dualSIM);
		L = NEXT(L);
	}
}

void insDepoisMarca(LIST* pL, char* marca, void* data)
{
	SMARTPHONE* sm_aux;
	LIST tmp = *pL;
	LIST_NODE* next, * aux;
	if (*pL == NULL)
	{
		*pL = insertIni(*pL, data);
	}
	else
	{
		while (tmp != NULL)
		{
			sm_aux = (SMARTPHONE*)DATA(tmp);
			if (strcmp(sm_aux->marca, marca) == 0)
			{
				next = NEXT(tmp);
				aux = newNode(data);
				NEXT(aux) = next;
				NEXT(tmp) = aux;
				return;
			}
			tmp = NEXT(tmp);
		}
	}
}
// Função que cria listas com elementos da lista L de índice par
LIST criarListaPar(LIST L)
{
	int i = 1;
	SMARTPHONE* sm_tmp, * sm_aux;
	LIST_NODE* tmp;
	LIST L2 = NULL, init = NULL;
	while (L != NULL)
	{
		sm_aux = (SMARTPHONE*)DATA(L);
		if (i % 2 == 0)
		{
			if (L2 == NULL)
			{
				sm_tmp = (SMARTPHONE*)malloc(sizeof(SMARTPHONE));
				strcpy(sm_tmp->marca, sm_aux->marca);
				strcpy(sm_tmp->modelo, sm_aux->modelo);
				sm_tmp->preco = sm_aux->preco;
				sm_tmp->dualSIM = sm_aux->dualSIM;
				tmp = newNode(sm_tmp);
				L2 = tmp;
				init = L2;
			}
			else
			{
				sm_tmp = (SMARTPHONE*)malloc(sizeof(SMARTPHONE));
				strcpy(sm_tmp->marca, sm_aux->marca);
				strcpy(sm_tmp->modelo, sm_aux->modelo);
				sm_tmp->preco = sm_aux->preco;
				sm_tmp->dualSIM = sm_aux->dualSIM;
				tmp = newNode(sm_tmp);
				NEXT(L2) = tmp;
				L2 = NEXT(L2);
			}
		}
		L = NEXT(L);
		++i;
	}
	return init;
}
// Função que conta telemóveis dual-SIM da marca X
tuple<int, char*> contarMarcaDual(LIST L)
{
	SMARTPHONE* tmp = NULL;
	int count = 0;
	char* aux;
	aux = (char*)malloc(MAX_NOME * sizeof(char));
	printf("Marca: ");
	scanf(" %[^\n]", aux);
	while (L != NULL)
	{
		tmp = (SMARTPHONE*)DATA(L);
		if (tmp->dualSIM == TRUE && strcmp(tmp->marca, aux) == 0)
		{
			++count;
		}
		L = NEXT(L);
	}
	return { count, aux };
}
// Função que lê do ficheiro para a lista
STATUS ReadListFromFile(LIST* pL, const char* fName)
{
	FILE* fp;
	SMARTPHONE phone, * ptr;
	if ((fp = fopen(fName, "r")) != NULL)
	{
		while (!feof(fp)) {
			fscanf(fp, "%[^;];%[^;];%lf;%d\n", phone.marca, phone.modelo,
				&phone.preco, &phone.dualSIM);
			if (((ptr = (SMARTPHONE*)malloc(sizeof(SMARTPHONE))) != NULL) &&
				((*pL = insertIni(*pL, ptr)) != NULL))
			{
				strcpy(ptr->marca, phone.marca);
				strcpy(ptr->modelo, phone.modelo);
				ptr->preco = phone.preco;
				ptr->dualSIM = phone.dualSIM;
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
#define _CRT_SECURE_NO_WARNINGS

#include "Smartphone.h"

// Programa Principal

void EliminarEnd(LIST* list)
{
    LIST tmp, prev = NULL;
    if (*list != NULL)
    {
        if ((*list)->next == NULL)
        {
            free((*list)->data);
            free(*list);
            *list = NULL;
        }
        else
        {
            tmp = *list;
            while (tmp->next != NULL)
            {
                prev = tmp;
                tmp = tmp->next;
            }
            free(tmp->data);
            free(tmp);
            prev->next = NULL;
        }
    }
}

int main(int argc, char* argv[])
{
	char marca[] = "Huawei\0";
	SMARTPHONE sm;
	strcpy(sm.marca, "LG");
	strcpy(sm.modelo, "K8");
	sm.preco = 149.90;
	sm.dualSIM = TRUE;
    LIST L = NULL;
	if (!ReadListFromFile(&L, "Produtos.txt")) 
		return EXIT_FAILURE;
    ShowLista(L);
    EliminarEnd(&L);
    printf("\n------------------\n");
    ShowLista(L);
	return EXIT_SUCCESS;
}
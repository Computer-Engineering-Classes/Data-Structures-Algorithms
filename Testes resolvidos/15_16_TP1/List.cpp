#include "List.h"

// Fun��o que cria um n� da lista encadeada
LIST_NODE* newNode(void* data)
{
	LIST_NODE* newN;
	if ((newN = (LIST_NODE*)malloc(sizeof(LIST_NODE))) != NULL)
	{
		DATA(newN) = data;
		NEXT(newN) = NULL;
	}
	return(newN);
}
// Fun��o que insere um n� no in�cio da lista encadeada
LIST_NODE* insertIni(LIST L, void* data)
{
	LIST_NODE* newN;
	if ((newN = newNode(data)) != NULL)
		NEXT(newN) = L;
	return(newN);
}
#include "List.h"
#include "Smartphone.h"

void ShowLista(LIST list, void (*showFunc)(void*))
{
	while (list != NULL)
	{
		showFunc(DATA(list));
		list = NEXT(list);
	}
}

LIST_NODE* NewNode(void* data)
{
	LIST_NODE* new_node;
	if ((new_node = malloc(sizeof(LIST_NODE))) != NULL) {
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

STATUS ToCircular(LIST list)
{
	if (list == NULL)
	{
		return ERROR;
	}
	LIST start = list;
	while (NEXT(list) != NULL)
	{
		list = NEXT(list);
	}
	NEXT(list) = start;
	return OK;
}
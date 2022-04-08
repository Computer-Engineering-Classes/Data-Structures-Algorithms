#include "List.h"

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

void RemoveFirstNode(LIST* list)
{
	LIST_NODE* node;
	node = NEXT(*list);
	free(DATA(*list));
	free(*list);
	*list = node;
}
void FreeList(LIST* list)
{
	while (*list != NULL)
		RemoveFirstNode(list);
}
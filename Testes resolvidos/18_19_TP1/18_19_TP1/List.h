#pragma once

#include <stdlib.h>

#define DATA(node) ((node)->data)
#define NEXT(node) ((node)->next)

typedef enum _STATUS { ERROR, OK } STATUS;
typedef enum _BOOLEAN { FALSE, TRUE } BOOLEAN;

typedef struct _LIST_NODE
{
	void* data;
	struct _LIST_NODE* next;
} LIST_NODE;

typedef LIST_NODE* LIST;

LIST_NODE* NewNode(void*);
LIST_NODE* InsertIni(LIST*, void*);
void RemoveFirstNode(LIST* list);
void FreeList(LIST* list);
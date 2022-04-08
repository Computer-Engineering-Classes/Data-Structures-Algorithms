#pragma once

#include <stdlib.h>
#include <stdio.h>
#include<stdbool.h>

typedef enum class _LIST_LOCATION { LIST_START, LIST_END } LIST_LOCATION;
typedef enum class _STATUS { OK, ERROR } STATUS;

typedef struct _LIST_NODE
{
	void* data;
	struct _LIST_NODE* next;
} LIST_NODE;
typedef LIST_NODE* LIST;

#define DATA(node) ((node)->data)
#define NEXT(node) ((node)->next)
#define EMPTY NULL
#define NO_LINK NULL

void initList(LIST* list);
void deleteList(LIST* list);
bool emptyList(LIST list);
LIST_NODE* NewNode(void* data);
STATUS InsertIni(LIST* list, void* data);
STATUS InsertEnd(LIST* list, void* data);
int ListSize(LIST list);
void ShowValues(LIST list, void (*ShowValues)(LIST));
int fpeek(FILE* stream);
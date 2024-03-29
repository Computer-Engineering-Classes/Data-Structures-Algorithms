#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>

typedef enum _STATUS { ERROR, OK } STATUS;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;

#define DATA(node) ((node)->data)
#define NEXT(node) ((node)->next)

// Defini��o da estrutura LIST_NODE
typedef struct _LIST_NODE {
	void* data;
	struct _LIST_NODE* next;
} LIST_NODE;
typedef LIST_NODE* LIST;
//Declara��o das fun��es
LIST_NODE* newNode(void*);
LIST_NODE* insertIni(LIST, void*);

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DATA(node) ((node)->data)
#define NEXT(node) ((node)->next)

typedef enum _STATUS { ERROR, OK } STATUS;

typedef struct _LIST_NODE
{
	void* data;
	struct _LIST_NODE* next;
} LIST_NODE;

typedef LIST_NODE* LIST;

LIST_NODE* NewNode(void*);
LIST_NODE* InsertIni(LIST*, void*);
STATUS ToCircular(LIST);
void ShowLista(LIST, void (*showFunc)(void*));
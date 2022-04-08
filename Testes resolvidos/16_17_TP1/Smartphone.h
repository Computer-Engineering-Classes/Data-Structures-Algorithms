#pragma once
#pragma warning(disable:6031)

#include "List.h"

#define MAX_NOME 20

typedef struct _SMARTPHONE {
	char marca[MAX_NOME];
	char modelo[MAX_NOME];
	float preco;
	int stock;
} SMARTPHONE;

void ShowSmartphone(SMARTPHONE* smartphone);
void ReadK(SMARTPHONE* smartphone);
STATUS AddSmartphone(LIST* list);
void ValorTotal(LIST list);
STATUS ReadFile(LIST*, const char*);
void DelStockZero(LIST*);
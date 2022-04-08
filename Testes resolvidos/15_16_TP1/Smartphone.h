#pragma once

#include "List.h"
#include <stdio.h>
#include <string.h>
#include <tuple>

#define MAX_NOME 20

using namespace std;

// Definição da estrutura SMARTPHONE
typedef struct _SMARTPHONE 
{
	char marca[MAX_NOME];
	char modelo[MAX_NOME];
	double preco;
	BOOLEAN dualSIM; // TRUE quer dizer que é dual SIM
} SMARTPHONE;

STATUS ReadListFromFile(LIST*, const char*);
tuple<int, char*> contarMarcaDual(LIST L);
LIST criarListaPar(LIST L);
void insDepoisMarca(LIST* pL, char* marca, void* data);
void ShowLista(LIST L);

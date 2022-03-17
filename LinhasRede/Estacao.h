#pragma once
#include "List.h"

#define MAX_BUF 50
#define MAX 30
#define NO_LINHAS 5

typedef struct _ESTACAO
{
    char desig[MAX];
    float custo;
    bool ativa;
    bool no;
} ESTACAO;

ESTACAO* ReadEstacao(FILE* fp);
ESTACAO* ReadKEstacao();
void SaveEstacao(FILE* fp, ESTACAO* est);

void InitLinhas(LIST* Linhas);
void MostrarLinhas(LIST* Linhas);
void LerLinhas(LIST* Linhas);
void GuardarLinhas(LIST* Linhas);
STATUS AtivarEstacao(LIST* Linhas);
STATUS AdicionarEstacao(LIST* Linhas);
STATUS EliminarEstacao(LIST* Linhas);
float CustoViagem(LIST* Linhas);
LIST_NODE* FindEstacao(LIST* Linhas, char* desig);
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
void ShowLinhas(LIST* Linhas);
void ReadLinhas(LIST* Linhas);
void SaveLinhas(LIST* Linhas);
STATUS ActEstacao(LIST* Linhas);
STATUS AddEstacao(LIST* Linhas);
STATUS AddPosEstacao(LIST* Linhas);
STATUS DelEstacao(LIST* Linhas);
float CustoViagem(LIST* Linhas);
LIST_NODE* FindEstacao(LIST* Linhas, char* desig);
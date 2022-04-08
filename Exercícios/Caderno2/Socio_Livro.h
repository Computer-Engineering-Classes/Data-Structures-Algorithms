#pragma once

#include "ListaEncadeada.h"
#include <string.h>

#define MAX 50
#define MAX_REQ 5

typedef struct _LIVRO
{
	char autor[MAX];
	char titulo[MAX]; 
	int no_disp;
} LIVRO;

typedef struct _SOCIO
{
	char nome[MAX];
	int numero;
	int n_req;
	LIVRO* requisitado[MAX_REQ];
} SOCIO;

void ShowValuesLivro(LIST list);
void ShowValuesSocio(LIST list);
void consultarLivro(LIST livro_list);
void consultarSocio(LIST socio_list);
void requisitarLivro(LIST* livro_list, LIST* socio_list);
void entregarLivro(LIST* livro_list, LIST* socio_list);
void addLivro(LIST* list);
void addSocio(LIST* list);
void delLivro(LIST* livro_list, LIST socio_list);
void verifySocioLivro(LIST_NODE* livro, LIST socio_list);
void delSocio(LIST* socio_list, LIST livro_list);
void verifyLivroSocio(LIST_NODE* socio);
void readFiles(LIST* socio_list, LIST* livro_list);
void writeFiles(LIST livro_list, LIST socio_list);

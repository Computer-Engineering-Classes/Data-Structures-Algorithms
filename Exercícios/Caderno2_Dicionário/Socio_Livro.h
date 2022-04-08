#pragma once
#include "Dicionario.h"

#define MAX 50

typedef struct _LIVRO {
	char* autor;
	char* titulo;
	int estado;
}LIVRO;

typedef struct _SOCIO {
	char* nome;
	int numero;
	void** livro;
} SOCIO;

void addSocio(Dictionary socios);
STATUS delSocio(Dictionary socios, Dictionary livros, char* s);
void estadoSocio(Dictionary socios, char* n);
void PrintSocio(void* data);
void deleteSocio(void* data);
void addLivro(Dictionary livros);
DicItem* searchLivros(Dictionary livros, char* a, char* t); //Procura pelo nome e autor
void estadoLivro(Dictionary livros, char* a, char* t);
void PrintLivro(void* data);
STATUS delLivro(Dictionary livros, Dictionary socios, char* a, char* s);
STATUS verifySociosLivros(Dictionary socios, LIVRO* l);
void deleteLivro(void* data);
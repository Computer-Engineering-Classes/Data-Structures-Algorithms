#pragma once
#include "Dicionario.h"
#include "Socio_Livro.h"

char fpeek(FILE* stream);
void readFiles(Dictionary socios, Dictionary livros);
void writeFiles(Dictionary socios, Dictionary livros);
void requisitarLivro(Dictionary socios, Dictionary livros, char* a, char* t, char* s);
void atribuirLivro(Dictionary socios, Dictionary livros, char* a, char* t, char* s);
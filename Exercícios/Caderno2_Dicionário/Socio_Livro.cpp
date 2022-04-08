#include "Socio_Livro.h"

void addLivro(Dictionary livros) {

	char s[150];
	LIVRO* l;
	if ((l = (LIVRO*)malloc(sizeof(LIVRO))) != NULL) {
		printf("Livro:\n");
		printf("Autor: ");
		strcpy(s, "\0");
		scanf(" %[^\n]", s);
		l->autor = (char*)malloc(sizeof(char) * 150);
		strcpy(l->autor, s);
		strcpy(s, "\0");
		printf("Titulo: ");
		scanf(" %[^\n]", s);
		l->titulo = (char*)malloc(sizeof(char) * 150);
		strcpy(l->titulo, s);
		l->estado = 0;
		char* s;
		s = (char*)malloc(sizeof(char) * (strlen(l->autor) + strlen(l->titulo)));
		strcpy(s, l->autor);
		strcat(s, l->titulo);
		add(livros, s, l, deleteLivro);
	}

}

void PrintLivro(void* data) {
	printf(" %s - %s - %d\n", ((LIVRO*)data)->autor, ((LIVRO*)data)->titulo, ((LIVRO*)data)->estado);
}

DicItem* searchLivros(Dictionary livros, char* a, char* t) {

	if (livros != NULL && livros->count > 0) {

		void* data;
		char* n = (char*)malloc(sizeof(char) * (strlen(a) + strlen(t) + 1));

		strcpy(n, a);
		strcat(n, t);

		if ((data = search(livros, n)) != NULL) {
			return (DicItem*)data;
		}
		else
			printf("O livro nao existe!!!");

		free(n);
	}
	else
		printf("Nao existem livros!!!");

	return nullptr;
}

void estadoLivro(Dictionary livros, char* a, char* t) {

	DicItem* data;

	if ((data = searchLivros(livros, a, t)) != NULL) {
		if (((LIVRO*)DATA(data))->estado > 0) {
			printf("O livro tem %d copias requisitadas!!", ((LIVRO*)DATA(data))->estado);
		}
		else {
			printf("O livro nao tem copias requisitadas!!");
		}
	}
	else
		printf("O livro nao existe!!!");
}

void deleteLivro(void* data) {

	free(((LIVRO*)data)->autor);
	free(((LIVRO*)data)->titulo);

}

STATUS delLivro(Dictionary livros, Dictionary socios, char* a, char* t) {

	DicItem* livro;

	if ((livro = searchLivros(livros, a, t)) != NULL) {
		if (verifySociosLivros(socios, (LIVRO*)DATA(livro))) {
			char* n = (char*)malloc(sizeof(char) * (strlen(a) + strlen(t) + 1));
			strcpy(n, a);
			strcat(n, t);
			return deleteItem(livros, n, deleteLivro);
		}
	}

	return ERROR;
}

STATUS verifySociosLivros(Dictionary socios, LIVRO* l) {

	if (socios != NULL && socios->count > 0) {
		int i = 0;
		int j = 1;
		int n = 0;
		DicItem* item = NULL;
		for (i = 0; i < socios->size; i++) {
			item = socios->items[i];
			if (item && DATA(item) && ((SOCIO*)DATA(item))->livro != NULL) {
				j = 1;
				n = *((int*)((SOCIO*)DATA(item))->livro[0]);
				for (j = 1; j < n && (strcmp(((LIVRO*)((SOCIO*)DATA(item))->livro[j])->titulo, l->titulo) != 0); j++);
				if (j < n) {
					for (; j < n - 1; j++) {
						((SOCIO*)DATA(item))->livro[j] = ((SOCIO*)DATA(item))->livro[j + 1];
					}
					((SOCIO*)DATA(item))->livro[n - 1] = NULL;
					*((int*)((SOCIO*)DATA(item))->livro[0]) = j;
					if ((((SOCIO*)DATA(item))->livro = (void**)realloc(((SOCIO*)DATA(item))->livro, sizeof(void*) * j)) == NULL) {
						printf("uiui está mal isto!!!!");
						exit(-1);
					}
				}
			}
		}
		return OK;
	}

	return ERROR;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void addSocio(Dictionary socios) {

	char s[150];
	SOCIO* l;
	if ((l = (SOCIO*)malloc(sizeof(SOCIO))) != NULL) {
		printf("SOCIO:\n");
		printf("Nome: ");
		strcpy(s, "\0");
		scanf(" %[^\n]", s);
		l->nome = (char*)malloc(sizeof(char) * 150);
		strcpy(l->nome, s);
		strcpy(s, "\0");
		printf("Numero: ");
		scanf(" %d", &(l->numero));
		l->livro = NULL;
		add(socios, tostring(l->numero), l, deleteSocio);
	}

}

void estadoSocio(Dictionary socios, char* n) {

	if (socios != NULL && socios->count > 0) {

		DicItem* data;

		if ((data = search(socios, n)) != NULL) {
			if (((SOCIO*)DATA(data))->livro != NULL) {
				printf("O socio tem %d livros requisitados!!", (*((int*)((SOCIO*)DATA(data))->livro[0])) - 1);
			}
			else
			{
				printf("O socio nao tem livros requisitados!!!");
			}
		}
		else
			printf("O socio nao existe!!!");
	}
	else
		printf("Nao existem socios!!!");
}

void PrintSocio(void* data) 
{
	LIVRO* livro_tmp;
	printf(" %s - %d ", ((SOCIO*)data)->nome, ((SOCIO*)data)->numero);
	if (((SOCIO*)data)->livro != NULL) 
	{
		int  n = *((int*)((SOCIO*)data)->livro[0]);
		for (int i = 1; i < n; i++) 
		{
			livro_tmp = ((LIVRO*)((SOCIO*)data)->livro[i]);
			printf("- %s", livro_tmp->titulo);
		}
	}
	printf("\n");

}

STATUS delSocio(Dictionary socios, Dictionary livros, char* s) 
{
	DicItem* item;
	LIVRO* aux;

	if ((item = search(socios, s)) != NULL) {
		if (((SOCIO*)DATA(item))->livro != NULL) {
			int i = 1;
			int n = *((int*)((SOCIO*)DATA(item))->livro[0]);
			for (i = 1; i < n; i++) {
				if ((aux = (LIVRO*)DATA(searchLivros(livros, ((LIVRO*)((SOCIO*)DATA(item))->livro[i])->autor, ((LIVRO*)((SOCIO*)DATA(item))->livro[i])->titulo))) != NULL) {
					aux->estado--;
				}
			}
			deleteItem(socios, tostring(((SOCIO*)DATA(item))->numero), deleteSocio);
			return OK;
		}
	}
	return ERROR;
}

void deleteSocio(void* data) 
{
	free(((SOCIO*)data)->nome);
	if (((SOCIO*)data)->livro != NULL)
	{
		free(((SOCIO*)data)->livro[0]);
		free(((SOCIO*)data)->livro);
	}
}
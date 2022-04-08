#include "Menu.h"

void readFiles(Dictionary socios, Dictionary livros) {
	FILE* fp;

	//free dos socios e dos livros
	emptyDictionary(livros, deleteLivro);
	emptyDictionary(socios, deleteSocio);

	if (fp = fopen("livros.txt", "r")) {
		LIVRO* p;
		int b = 0;
		char* s = NULL;
		while (!feof(fp)) {
			p = (LIVRO*)malloc(sizeof(LIVRO));
			p->autor = (char*)malloc(sizeof(char) * MAX);
			p->titulo = (char*)malloc(sizeof(char) * MAX);
			fscanf(fp, "%[^;];%[^;];%d;\n", p->autor, p->titulo, &(p->estado));
			s = (char*)malloc(1 + sizeof(char) * (strlen(p->autor) + strlen(p->titulo)));
			strcpy(s, p->autor);
			strcat(s, p->titulo);
			add(livros, s, p, deleteLivro);
			free(s);
			p = NULL;
		}
		fclose(fp);
	}

	if (fp = fopen("socios.txt", "r")) {
		SOCIO* p;
		DicItem* l;
		char a[MAX] = "", s[MAX] = "";
		int size = 1;
		int* f = NULL;
		
		while (!feof(fp)) {
			p = (SOCIO*)malloc(sizeof(SOCIO));
			p->nome = (char*)malloc(sizeof(char) * MAX);
			fscanf(fp, "%[^;];%d;", p->nome, &p->numero);
			p->livro = NULL;
			size = 1;
			while (fpeek(fp) != '\n') 
			{
				if (size == 1)
				{
					p->livro = (void**)malloc(sizeof(void*));
					p->livro[0] = (int*)malloc(sizeof(int));
				}
				fscanf(fp, "%[^,],", s);
				fscanf(fp, "%[^;];", a);
				if ((l = searchLivros(livros, a, s)) != NULL) 
				{

					if ((p->livro = (void**)realloc(p->livro, (size + 1) * sizeof(void*))) == NULL) 
					{
						exit(-1);
					}
					f = (int*)malloc(sizeof(int));
					if (f != NULL) {
						*f = (size + 1);
						p->livro[0] = f;
						f = NULL;
					}
					p->livro[size++] = (LIVRO*)DATA(l);
				}
			}
			fscanf(fp, "\n");

			add(socios, tostring(p->numero), p, deleteSocio);
			p = NULL;
			l = NULL;
		}
		fclose(fp);
	}
}

char fpeek(FILE* stream)
{
	char c;
	c = fgetc(stream);
	ungetc(c, stream);
	return c;
}

void writeFiles(Dictionary socios, Dictionary livros)
{
	FILE* fp;

	if (fp = fopen("livros.txt", "w")) 
	{
		for (int i = 0; i < livros->size; i++)
		{
			if(livros->items[i] != NULL)
			fprintf(fp, "%s;%s;%d;\n", ((LIVRO*)DATA(livros->items[i]))->autor, 
				((LIVRO*)DATA(livros->items[i]))->titulo, ((LIVRO*)DATA(livros->items[i]))->estado);
		}
		fclose(fp);
	}
	if (fp = fopen("socios.txt", "w")) 
	{
		int n = 0;
		for (int i = 0; i < socios->size; i++)
		{
			if (socios->items[i] != NULL)
			{
				fprintf(fp, "%s;%d;", ((SOCIO*)DATA(socios->items[i]))->nome, ((SOCIO*)DATA(socios->items[i]))->numero);
				n = *((int*)((SOCIO*)DATA(socios->items[i]))->livro[0]);
				for (int j = 1; j < n; j++)
				{
					fprintf(fp, "%s,%s", ((LIVRO*)((SOCIO*)DATA(socios->items[i]))->livro[j])->titulo,
						((LIVRO*)((SOCIO*)DATA(socios->items[i]))->livro[j])->autor);
					if (j == (n - 1))
						fprintf(fp, ";\n");
					else
						fprintf(fp, ";");
				}
			}
		}
		fclose(fp);
	}
}

void requisitarLivro(Dictionary socios, Dictionary livros, char* a, char* t, char* s) {

	DicItem* livro;
	DicItem* socio;

	if ((livro = searchLivros(livros, a, t)) != NULL && (socio = search(socios, s)) != NULL) {
		if (((SOCIO*)DATA(socio))->livro != NULL) {
			int size = *((int*)((SOCIO*)DATA(socio))->livro[0]);
			if ((((SOCIO*)DATA(socio))->livro = (void**)realloc(((SOCIO*)DATA(socio))->livro, sizeof(void*) * (size + 1))) != NULL) {
				((LIVRO*)DATA(livro))->estado++;
				((SOCIO*)DATA(socio))->livro[size++] = DATA(livro);
				*((int*)((SOCIO*)DATA(socio))->livro[0]) = size;
				printf("Livro requisitado com sucesso!!!");
			}
		}
		else {
			if ((((SOCIO*)DATA(socio))->livro = (void**)malloc(sizeof(void*) * 2)) != NULL) {
				((LIVRO*)DATA(livro))->estado++;
				((SOCIO*)DATA(socio))->livro[1] = DATA(livro);
				((SOCIO*)DATA(socio))->livro[0] = (int*)malloc(sizeof(int));
				*((int*)((SOCIO*)DATA(socio))->livro[0]) = 2;
				printf("Livro requisitado com sucesso!!!");
			}
		}
	}
	else
		printf("O socio ou o livro nao existem!!!\nPor favor insira socios e livros antes de poder utilizar esta funcionalidade");
}

void atribuirLivro(Dictionary socios, Dictionary livros, char* a, char* t, char* s) {

	requisitarLivro(socios, livros, a, t, s);

}

char* tostring(int num) {
	int i, rem, len = 0, n;
	char* str;

	n = num;
	while (n != 0) {
		len++;
		n /= 10;
	}

	str = (char*)malloc(sizeof(char) * (len + 1));

	for (i = 0; i < len; i++) {
		rem = num % 10;
		num = num / 10;
		str[len - (i + 1)] = (char)(rem + (int)'0');
	}
	str[len] = '\0';
	return str;
}
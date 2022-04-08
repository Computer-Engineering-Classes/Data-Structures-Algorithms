#include "Socio_Livro.h"

int retval;

/****************************************************************
* Funcao: Escreve no ecra o conteudo da lista de livros
*
* Parametros: list - apontador para o primeiro no'
* Saida: void
***************************************************************/
void ShowValuesLivro(LIST list)
{
	while (list != NULL)
	{
		if(((LIVRO*)DATA(list))->no_disp > 1)
			printf(" (%s %s %d Exemplares) \n      ->", ((LIVRO*)DATA(list))->autor, ((LIVRO*)DATA(list))->titulo, ((LIVRO*)DATA(list))->no_disp);
		else
			printf(" (%s %s 1 Exemplar) \n      ->", ((LIVRO*)DATA(list))->autor, ((LIVRO*)DATA(list))->titulo);
		list = NEXT(list);
	}
}
/****************************************************************
* Funcao: Escreve no ecra o conteudo da lista de socios
*
* Parametros: list - apontador para o primeiro no'
* Saida: void
***************************************************************/
void ShowValuesSocio(LIST list)
{
	while (list != NULL)
	{
		printf(" (%d %s", ((SOCIO*)DATA(list))->numero, ((SOCIO*)DATA(list))->nome);
		int size = ((SOCIO*)DATA(list))->n_req;
		if(size==0)
			printf(" / NULL");
		else
			for (int i = 0; i < MAX_REQ; i++)
				if(((SOCIO*)DATA(list))->requisitado[i] != NULL)
					printf(" / %s %s", ((SOCIO*)DATA(list))->requisitado[i]->autor, ((SOCIO*)DATA(list))->requisitado[i]->titulo);
		printf(") \n      ->");
		list = NEXT(list);
	}
}
/****************************************************************
* Funcao: Procura a informacao de um livro pelo autor e titulo
*
* Parametros: livro_list - apontador para o primeiro no'
* Saida: void
***************************************************************/
void consultarLivro(LIST livro_list)
{
	LIVRO tmp;
	char titulo[MAX], autor[MAX];
	printf("\nTitulo do livro: ");
	retval = scanf(" %[^\n]", titulo);
	printf("\nAutor do livro: ");
	retval = scanf(" %[^\n]", autor);
	autor[MAX - 1] = '\0';
	titulo[MAX - 1] = '\0';
	while (livro_list != NULL)
	{
		tmp = *(LIVRO*)DATA(livro_list);
		if (strcmp(titulo, tmp.titulo) == 0 && strcmp(autor, tmp.autor) == 0)
		{
			if (tmp.no_disp == MAX_REQ)
			{
				printf("\nO livro \"%s\" de %s nao foi requisitado.\n", titulo, autor);
				return;
			}
			printf("\nO livro \"%s\" de %s tem %d exemplar(es) disponivel(eis).\n", titulo, autor, tmp.no_disp);
			return;
		}
		livro_list = NEXT(livro_list);
	}
	printf("\nO livro \"%s\" de %s nao se encontra registado.\n", titulo, autor);
}
/****************************************************************
* Funcao: Procurar a informacao de um socio pelo numero
*
* Parametros: socio_list - apontador para o primeiro no'
* Saida: void
***************************************************************/
void consultarSocio(LIST socio_list)
{
	SOCIO tmp;
	int numero;
	printf("\nNumero do socio: ");
	retval = scanf(" %d", &numero);
	while (socio_list != NULL)
	{
		tmp = *(SOCIO*)DATA(socio_list);
		if (tmp.numero == numero)
		{
			if (tmp.n_req > 0)
			{
				printf("\nO socio %s (%d) requisitou os livros:\n", tmp.nome, tmp.numero);
				for (int i = 0; i < tmp.n_req; i++)
					printf("\t-> \"%s\", de %s.\n", tmp.requisitado[i]->titulo, tmp.requisitado[i]->autor);
				return;
			}
			printf("\nO socio %s (%d) nao requisitou nenhum livro.\n", tmp.nome, tmp.numero);
			return;
		}
		socio_list = NEXT(socio_list);
	}
	printf("\nNao existe nenhum socio com o numero %d registado.\n", numero);
}
/****************************************************************
* Funcao: Permite requisitar um livro pelo autor, titulo e numero de socio
*
* Parametros: list - apontador para o primeiro no'
* Saida: void
***************************************************************/
void requisitarLivro(LIST* livro_list, LIST* socio_list)
{
	int num, i = 0;
	char titulo[MAX], autor[MAX];
	SOCIO* socio_tmp;
	LIVRO* livro_tmp;
	LIST tmp1, tmp2;
	printf("\nNumero do socio: ");
	retval = scanf(" %d", &num);
	tmp1 = *socio_list;
	while (tmp1 != NULL)
	{
		socio_tmp = (SOCIO*)DATA(tmp1);
		if (socio_tmp->numero == num)
		{
			if (socio_tmp->n_req == MAX_REQ)
			{
				printf("\nO socio %s (%d) ja requisitou o maximo numero de livros possiveis (%d).\n",
					socio_tmp->nome, socio_tmp->numero, MAX_REQ);
				return;
			}
			else
			{
				printf("\nTitulo do livro: ");
				retval = scanf(" %[^\n]", titulo);
				printf("\nAutor do livro: ");
				retval = scanf(" %[^\n]", autor);
				tmp2 = *livro_list;
				titulo[MAX - 1] = '\0';
				autor[MAX - 1] = '\0';
				while (tmp2 != NULL)
				{
					livro_tmp = (LIVRO*)DATA(tmp2);
					if (strcmp(livro_tmp->autor, autor) == 0 && strcmp(livro_tmp->titulo, titulo) == 0)
					{
						if (livro_tmp->no_disp > 1)
						{
							while (socio_tmp->requisitado[i] != NULL)
								++i;
							socio_tmp->requisitado[i] = livro_tmp;
							livro_tmp->no_disp -= 1;
							printf("\nO socio %s (%d) requisitou o livro \"%s\", de %s.\n", socio_tmp->nome, socio_tmp->numero,
								socio_tmp->requisitado[i]->titulo, socio_tmp->requisitado[i]->autor);
							++socio_tmp->n_req;
							return;
						}
						else
						{
							printf("\nO livro \"%s\" de %s so tem um exemplar disponivel.\n", livro_tmp->titulo, livro_tmp->autor);
							return;
						}
					}
					tmp2 = NEXT(tmp2);
				}
				printf("\nO livro \"%s\" de %s nao se encontra registado.\n", titulo, autor);
				return;
			}
		}
		tmp1 = NEXT(tmp1);
	}
	printf("\nNao existe nenhum socio com o numero %d registado.\n", num);
}
/*funcao para entregar um livro, através do número do sócio que faz a entrega.*/
void entregarLivro(LIST* livro_list, LIST* socio_list)
{
	int pos;
	LIST tmp;
	SOCIO* socio_tmp;
	int numero;
	printf("\nNumero do socio: ");
	retval = scanf(" %d", &numero);
	tmp = *socio_list;
	while (tmp != NULL)
	{
		socio_tmp = (SOCIO*)DATA(tmp);
		if (socio_tmp->numero == numero)
		{
			if (socio_tmp->n_req > 0)
			{
				printf("\nPosicao do livro (0 - %d): ", MAX_REQ);
				retval = scanf(" %d", &pos);
				if (socio_tmp->requisitado[pos] == NULL)
				{
					printf("\nO socio %s (%d) já entregou o livro.\n", socio_tmp->nome, socio_tmp->numero);
					return;
				}
				printf("\nO socio %s (%d) entregou o livro \"%s\", de %s.\n", socio_tmp->nome, socio_tmp->numero
					, socio_tmp->requisitado[pos]->titulo, socio_tmp->requisitado[pos]->autor);
				socio_tmp->requisitado[pos]->no_disp += 1;
				socio_tmp->requisitado[pos] = NULL;
				socio_tmp->n_req -= 1;
				return;
			}
			printf("\nO socio %s (%d) nao requisitou nenhum livro.\n", socio_tmp->nome, socio_tmp->numero);
			return;
		}
		tmp = NEXT(tmp);
	}
	printf("\nNao existe nenhum socio com o numero %d registado.\n", numero);
}
//funcao para adicionar um livro
void addLivro(LIST* list)
{
	LIVRO* livro_tmp;
	if ((livro_tmp = (LIVRO*)malloc(sizeof(LIVRO))) != NULL)
	{
		printf("\nTitulo do livro: ");
		retval = scanf(" %[^\n]", livro_tmp->titulo);
		printf("\nNome do autor: ");
		retval = scanf(" %[^\n]", livro_tmp->autor);
		livro_tmp->no_disp = MAX_REQ;
		InsertIni(list, livro_tmp);
	}
	else
	{
		printf("\nERRO na alocacao de memoria.\n");
		exit(-1);
	}
}
//funcao para adicionar socio
void addSocio(LIST* list)
{
	SOCIO* socio_tmp;
	if ((socio_tmp = (SOCIO*)malloc(sizeof(SOCIO))) != NULL)
	{
		printf("\nNome do socio: ");
		retval = scanf(" %[^\n]", socio_tmp->nome);
		printf("\nNumero do socio: ");
		retval = scanf(" %d", &socio_tmp->numero);
		for (int i = 0; i < MAX_REQ; i++)
			socio_tmp->requisitado[i] = NULL;
		InsertIni(list, socio_tmp);
	}
	else
	{
		printf("\nERRO na alocacao de memoria.\n");
		exit(-1);
	}
}
//funcao para remover apontador de livro do socio_list
void verifySocioLivro(LIST_NODE* livro, LIST socio_list)
{
	if (((LIVRO*)DATA(livro))->no_disp < MAX_REQ)
	{
		for (LIST tmp2 = socio_list; tmp2 != NULL; tmp2 = NEXT(tmp2))
		{
			for (int i = 0; i < MAX_REQ; i++)
			{
				if (((SOCIO*)DATA(tmp2))->requisitado[i] == (LIVRO*)DATA(livro))
				{
					((SOCIO*)DATA(tmp2))->requisitado[i] = NULL;
					((LIVRO*)DATA(livro))->no_disp++;
				}
				if (((LIVRO*)DATA(livro))->no_disp == 5) return;
			}
		}
	}
}
//funcao para remover livro
void delLivro(LIST* livro_list, LIST socio_list)
{
	char buffer[MAX];
	LIST tmp, prev;
	printf("\nTitulo do livro: ");
	retval = scanf(" %[^\n]", buffer);
	tmp = *livro_list;
	buffer[MAX-1] = '\0';
	if (strcmp(((LIVRO*)DATA(tmp))->titulo, buffer) == 0)
	{
		verifySocioLivro(tmp, socio_list);
		*livro_list = NEXT(tmp);
		free(DATA(tmp));
		free(tmp);
	}
	else
	{
		prev = tmp;
		tmp = NEXT(tmp);
		while (tmp != NULL)
		{
			prev = tmp;
			if (strcmp(((LIVRO*)DATA(tmp))->titulo, buffer) == 0)
			{
				verifySocioLivro(tmp, socio_list);
				NEXT(prev) = NEXT(tmp);
				free(DATA(tmp));
				free(tmp);
				return;
			}
			prev = tmp;
			tmp = NEXT(tmp);
		}
		printf("\nERRO livro nao presente.\n");
	}
}
//funcao para repor numero de exemplares disponiveis dos livros de um socio
void verifyLivroSocio(LIST_NODE* socio)
{
	for (int i = 0; i < MAX_REQ; i++)
	{
		if (((SOCIO*)DATA(socio))->requisitado[i] != NULL)
		{
			((SOCIO*)DATA(socio))->requisitado[i]->no_disp += 1;
		}
	}
}
//funcao para remover socio
void delSocio(LIST* socio_list, LIST livro_list)
{
	int num;
	LIST tmp, prev;
	printf("\nNumero do socio: ");
	retval = scanf(" %d", &num);
	tmp = *socio_list;
	if (((SOCIO*)DATA(tmp))->numero == num)
	{
		verifyLivroSocio(tmp);
		*socio_list = NEXT(tmp);
		free(DATA(tmp));
		free(tmp);
	}
	else
	{
		prev = tmp;
		tmp = NEXT(tmp);
		while (tmp != NULL)
		{
			if (((SOCIO*)DATA(tmp))->numero == num)
			{
				verifyLivroSocio(tmp);
				NEXT(prev) = NEXT(tmp);
				free(DATA(tmp));
				free(tmp);
				return;
			}
			prev = tmp;
			tmp = NEXT(tmp);
		}
		printf("\nERRO socio nao presente.\n");
	}
}
//funcao de leitura das listas de livros e socios a partir de ficheiros
void readFiles(LIST* socio_list, LIST* livro_list)
{
	int pos, i = 0, size = 0;
	LIST tmp;
	SOCIO* socio_tmp;
	LIVRO* livro_tmp;
	LIVRO** lp = NULL;
	FILE* socio_fp, * livro_fp;
	if ((socio_fp = fopen("socios.txt", "rt")) == NULL || (livro_fp = fopen("livros.txt", "rt")) == NULL)
	{
		printf("\nERRO na abertura dos ficheiros.\n");
		exit(-1);
	}
	//Leitura do ficheiro livros.txt
	while (!feof(livro_fp))
	{
		if ((livro_tmp = (LIVRO*)malloc(sizeof(LIVRO))) == NULL)
		{
			printf("\nERRO na alocacao de memoria.\n");
			exit(-1);
		}
		retval = fscanf(livro_fp, "%[^;];", livro_tmp->autor);
		retval = fscanf(livro_fp, "%[^;];", livro_tmp->titulo);
		retval = fscanf(livro_fp, "%d;\n", &livro_tmp->no_disp);
		InsertEnd(livro_list, livro_tmp);
	}
	//vetor de apontadores dos livros
	size = ListSize(*livro_list);
	if (size == 0 || (lp = (LIVRO**)malloc(size * sizeof(LIVRO*))) == NULL)
	{
		printf("\nERRO na alocacao de memoria.\n");
			exit(-1);
	}
	else
	{
		tmp = *livro_list;
		while (tmp != NULL)
		{
			lp[i] = (LIVRO*)DATA(tmp);
			++i;
			tmp = NEXT(tmp);
		}
		fclose(livro_fp);
		//Leitura do ficheiro socios.txt
		while (!feof(socio_fp))
		{
			if ((socio_tmp = (SOCIO*)malloc(sizeof(SOCIO))) == NULL)
			{
				printf("\nERRO na alocacao de memoria.\n");
				exit(-1);
			}
			retval = fscanf(socio_fp, "%[^;];", socio_tmp->nome);
			retval = fscanf(socio_fp, "%d;", &socio_tmp->numero);
			size = 0;
			for (i = 0; i < MAX_REQ; i++)
			{
				retval = fscanf(socio_fp, "%d;", &pos);
				if (pos == -1)
					socio_tmp->requisitado[i] = NULL;
				else
				{
					socio_tmp->requisitado[i] = lp[pos];
					++size;
				}
			}
			socio_tmp->n_req = size;
			InsertEnd(socio_list, socio_tmp);
			retval = fscanf(socio_fp, "\n");
		}
		fclose(socio_fp);
		free(lp);
	}
}
//funcao de escrita das listas nos ficheiros
void writeFiles(LIST livro_list, LIST socio_list)
{
	int pos;
	LIST tmp;
	FILE* fp;
	LIVRO* req_tmp;
	//escrita no ficheiro socios.txt
	if ((fp = fopen("socios.txt", "wt")) == NULL)
	{
		printf("\nERRO na abertura do ficheiro.\n");
		exit(-1);
	}
	do
	{
		if (((SOCIO*)DATA(socio_list))->requisitado == NULL)
			fprintf(fp, "%s;%d;-1;\n", ((SOCIO*)DATA(socio_list))->nome, ((SOCIO*)DATA(socio_list))->numero);
		else
		{
			tmp = livro_list;
			fprintf(fp, "%s;%d;", ((SOCIO*)DATA(socio_list))->nome, ((SOCIO*)DATA(socio_list))->numero);
			for (int i = 0; i < MAX_REQ; i++)
			{
				req_tmp = ((SOCIO*)DATA(socio_list))->requisitado[i];
				if (req_tmp == NULL)
					fprintf(fp, "-1;");
				else
				{
					pos = 0;
					while (req_tmp != (LIVRO*)DATA(tmp))
					{
						++pos;
						tmp = NEXT(tmp);
					}
					fprintf(fp, "%d;", pos);
				}
			}
			fputc('\n', fp);
		}
	} while ((socio_list = NEXT(socio_list)) != NULL);
	fclose(fp);
	//escrita no ficheiro livros.txt
	if ((fp = fopen("livros.txt", "wt")) == NULL)
	{
		printf("\nERRO na abertura do ficheiro.\n");
		exit(-1);
	}
	do
	{
		fprintf(fp, "%s;%s;%d;\n", ((LIVRO*)DATA(livro_list))->autor, ((LIVRO*)DATA(livro_list))->titulo
			, ((LIVRO*)DATA(livro_list))->no_disp);
	} while ((livro_list = NEXT(livro_list)) != NULL);
	fclose(fp);
}

#include "ListaEncadeada.h"

/****************************************************************
* Funcao: Inicializa a lista
*
* Parametros: list - apontador para lista
* (duplo apontador para o primeiro no')
* Saida: void
***************************************************************/
void initList(LIST* list)
{
	*list = NULL;
}
/****************************************************************
* Funcao: Apaga os conteudos da lista
* 
* Parametros: list - apontador para list
* (duplo apontador para o primeiro no')
* Saida: void
****************************************************************/
void deleteList(LIST* list)
{
	LIST tmp = *list;
	LIST aux = NEXT(tmp);
	if (emptyList(*list) == true)
		return;
	while (aux != NULL)
	{
		free(DATA(tmp));
		free(tmp);
		tmp = aux;
		aux = NEXT(tmp);
	}
	free(DATA(tmp));
	free(tmp);
}
/****************************************************************
* Funcao: verifica se a lista é vazia
*
* Parametros: list - apontador para lista
* Saida: TRUE se a lista for vazia, ERROR caso contrário
***************************************************************/
bool emptyList(LIST list)
{
	return (list == NULL) ? true : false;
}
/****************************************************************
* Funcao: Cria um no'
*
* Parametros: data - apontador generico para os dados a inserir no no' criado
* Saida: apontador para o no' criado ou NULL em caso de erro
***************************************************************/
LIST_NODE* NewNode(void* data)
{
	LIST_NODE* new_node;
	if ((new_node = (LIST_NODE*)malloc(sizeof(LIST_NODE))) != NULL)
	{
		DATA(new_node) = data;
		NEXT(new_node) = NULL;
	}
	return(new_node);
}
/****************************************************************
* Funcao: Insere um no' no inicio da lista
*
* Parametros: list - apontador para lista
* (duplo apontador para o primeiro no')
* data - apontador generico para os dados a inserir no no' criado
* Saida: OK se o nó foi inserido na LISTA e ERROR caso contrário
***************************************************************/
STATUS InsertIni(LIST* list, void* data)
{
	LIST_NODE* new_node;
	if ((new_node = NewNode(data)) != NULL)
	{
		NEXT(new_node) = *list;
		*list = new_node;
		return STATUS::OK;
	}
	return STATUS::ERROR;
}
/****************************************************************
* Funcao: Insere um no' no fim da lista
*
* Parametros: list - apontador para lista
* (duplo apontador para o primeiro no')
* data - apontador generico para os dados a inserir no no' criado
* Saida: OK se o nó foi inserido na LISTA e ERROR caso contrário
***************************************************************/
STATUS InsertEnd(LIST* list, void* data)
{
	LIST_NODE* new_node, * temp;
	if ((new_node = NewNode(data)) != NULL)
	{
		if (*list == NULL)
			*list = new_node;
		else
		{
			temp = *list;
			while (NEXT(temp) != NULL)
				temp = NEXT(temp);
			NEXT(temp) = new_node;
		}
		return(STATUS::OK);
	}
	return(STATUS::ERROR);
}
/***************************************************************************
* Funcao: calcula quantos elementos contem a lista
*
* Parametros: list - apontador para uma lista
* Saida: numero de elementos da lista
***************************************************************************/
int ListSize(LIST list)
{
	int count = 0;
	while (list != NULL)
	{
		count++;
		list = NEXT(list);
	}
	return count;
}
/****************************************************************
* Funcao: Escreve no ecra o conteudo da lista
*
* Parametros: list - apontador para o primeiro no'
* Saida: void
***************************************************************/
void ShowValues(LIST list, void (*ShowValues)(LIST))
{
	if (emptyList(list) == true)
	{
		printf("\nLista vazia.\n");
		return;
	}
	printf("\nLISTA ->");
	(*ShowValues)(list);
	printf(" FIM\n");
}
/**************************************************************
*Funcao: Vê o caracter seguinte no ficheiro, sem o retirar
* 
* Parametros: stream - apontador para o ficheiro
* Saida: caracter seguinte na stream
**************************************************************/
int fpeek(FILE* stream)
{
	int c = fgetc(stream);
	ungetc(c, stream);
	return c;
}
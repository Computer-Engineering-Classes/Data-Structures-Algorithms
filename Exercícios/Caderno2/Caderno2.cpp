#include "Socio_Livro.h"
#include <conio.h>

int main(int argc, char* argv[])
{
	int opcao;
	LIST socio_list, livro_list;
	initList(&livro_list);
	initList(&socio_list);
	readFiles(&socio_list, &livro_list);
	//MENU
	while (true)
	{
		printf("\n\tMenu:\n");
		printf("\n\t1 - Adicionar livro\n");
		printf("\n\t2 - Remover livro\n");
		printf("\n\t3 - Adicionar socio\n");
		printf("\n\t4 - Remover socio\n");
		printf("\n\t5 - Consultar estado de um livro\n");
		printf("\n\t6 - Consultar estado de um socio\n");
		printf("\n\t7 - Requisitar um livro\n");
		printf("\n\t8 - Entregar um livro\n");
		printf("\n\t9 - Consultar listas de livros e socios\n");
		printf("\n\t10 - Sair\n");
		printf("\nOpcao: ");
		if (scanf(" %d", &opcao) == EOF)
		{
			printf("\nERRO de input.\n");
			exit(-1);
		}
		//system("cls");
		switch (opcao)
		{
		case 1:
			printf("\n\tAdicionar livro\n");
			addLivro(&livro_list);
			break;
		case 2:
			printf("\n\tRemover livro\n");
			delLivro(&livro_list, socio_list);
			break;
		case 3:
			printf("\n\tAdicionar socio\n");
			addSocio(&socio_list);
			break;
		case 4:
			printf("\n\tRemover socio\n");
			delSocio(&socio_list, livro_list);
			break;
		case 5:
			printf("\n\tConsultar estado de um livro\n");
			consultarLivro(livro_list);
			break;
		case 6:
			printf("\n\tConsultar estado de um socio\n");
			consultarSocio(socio_list);
			break;
		case 7:
			printf("\n\tRequisitar um livro\n");
			requisitarLivro(&livro_list, &socio_list);
			break;
		case 8:
			printf("\n\tEntregar um livro\n");
			entregarLivro(&livro_list, &socio_list);
			break;
		case 9:
			printf("\n\tConsultar listas de livros e socios\n");
			ShowValues(livro_list, &ShowValuesLivro);
			ShowValues(socio_list, &ShowValuesSocio);
			break;
		case 10:
			writeFiles(livro_list, socio_list);
			deleteList(&livro_list);
			deleteList(&socio_list);
			exit(0);
		default:
			printf("\nOpcao invalida.\n");
			break;
		}
	}
	return 0;
}
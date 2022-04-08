#include "Menu.h"
#include <conio.h>


int main(int argc, char* argv[])
{
	Dictionary livros = newDictionary();
	Dictionary socios = newDictionary();
	int opcao;
	//MENU
	while (TRUE)
	{
		printf("\n\tMenu:\n");
		printf("\n\t0 - Ler ficheiros\n");
		printf("\n\t1 - Adicionar livro\n");
		printf("\n\t2 - Remover livro\n");
		printf("\n\t3 - Adicionar socio\n");
		printf("\n\t4 - Remover socio\n");
		printf("\n\t5 - Consultar lista de livros\n");
		printf("\n\t6 - Consultar lista de socios\n");
		printf("\n\t7 - Consultar estado de um livro\n");
		printf("\n\t8 - Consultar estado de um socio\n");
		printf("\n\t9 - Requisitar um livro\n");
		printf("\n\t10 - Entregar um livro\n");
		printf("\n\t11 - Sair\n");
		printf("\nOpcao: ");
		if (!scanf(" %d", &opcao))
		{
			printf("\nERRO de input.\n");
			exit(-1);
		}
		//system("cls");
		switch (opcao)
		{
		case 0:
			readFiles(socios, livros);
			break;
		case 1:
			printf("\n\tAdicionar livro\n");
			addLivro(livros);
			break;
		case 2:
			printf("\n\tRemover livro\n");
			char t[150];
			char a[150];
			printf("Insira o nome do livro que deseja apagar\n-> ");
			scanf_s(" %[^\n]", t, 150);
			printf("Insira o nome do autor\n-> ");
			scanf_s(" %[^\n]", a, 150);
			if (delLivro(livros, socios, a, t) == OK)
				printf("Livro apagado com sucesso!!!!");
			else {
				printf("Erro ao apagar o livro!!!!");
				exit(-1);
			}
			print(livros, PrintLivro);
			break;
		case 3:
			printf("\n\tAdicionar socio\n");
			addSocio(socios);
			break;
		case 4:
			printf("\n\tRemover socio\n");
			char s[150];
			printf("Insira o numero do socio que deseja apagar\n-> ");
			scanf_s(" %[^\n]", s, 150);
			if (delSocio(socios, livros, s) == OK)
				printf("Socio apagado com sucesso!!!!");
			else {
				printf("Erro ao apagar o socio!!!!");
				exit(-1);
			}
			print(socios, PrintSocio);
			break;
		case 5:
		{
			print(livros, PrintLivro);
			break;
		}
		case 6:
		{
			print(socios, PrintSocio);
			break;
		}
		case 7:
		{
			char a[150], t[150];
			printf("Insira o nome do autor\n-> ");
			scanf_s(" %[^\n]", a, 150);
			printf("Insira o nome do livro\n-> ");
			scanf_s(" %[^\n]", t, 150);
			estadoLivro(livros, a, t);
			break;
		}
		case 8:
		{
			char n[150];
			printf("Insira o numero do socio\n-> ");
			scanf_s(" %[^\n]", n, 150);
			estadoSocio(socios, n);
			break;
		}
		case 9:
		{
			char a[150], t[150], s[150];
			printf("Insira o numero do socio\n-> ");
			scanf_s(" %[^\n]", s, 150);
			printf("Insira o nome do autor\n-> ");
			scanf_s(" %[^\n]", a, 150);
			printf("Insira o nome do livro\n-> ");
			scanf_s(" %[^\n]", t, 150);
			requisitarLivro(socios, livros, a, t, s);
			break;
		}
		case 10:
		{
			char a[150], t[150], s[150];
			printf("Insira o numero do socio\n-> ");
			scanf_s(" %[^\n]", s, 150);
			printf("Insira o nome do autor\n-> ");
			scanf_s(" %[^\n]", a, 150);
			printf("Insira o nome do livro\n-> ");
			scanf_s(" %[^\n]", t, 150);
			atribuirLivro(socios, livros, a, t, s);
			break;
		}
		case 11:
		{
			//free dos socios e dos livros
			writeFiles(socios, livros);
			deleteDictionary(livros, deleteLivro);
			deleteDictionary(socios, deleteSocio);
			exit(0);
			break;
		}
		default:
			printf("\nOpcao invalida.\n");
			break;
		}
	}
	return 0;
}
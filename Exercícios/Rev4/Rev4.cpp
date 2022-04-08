#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#define NSTRING 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;

typedef struct _CLIENT 
{
	int client_code;
	char name[NSTRING];
} CLIENT;

int ReadClients(CLIENT**, char*);

int main(void)
{
	int num_clients, i;
	CLIENT* clients = NULL;
	char str[NSTRING];
	
	setlocale(LC_ALL, "");
	
	printf("\nNome do ficheiro : ");
	fgets(str, NSTRING, stdin);
	strtok(str, "\n");
	switch (num_clients = ReadClients(&clients, str))
	{
	case -2: 
		printf("\a\nErro na alocação de memória...\n");
		break;
	case -1: 
		printf("\a\nErro de leitura do ficheiro...\n");
		break;
	case 0: 
		printf("\a\nFicheiro vazio...\n");
		break;
	default: 
		printf("\nFicheiro lido com sucesso...\n");
		printf("\nConteúdo do ficheiro:\n");
		for (i = 0; i < num_clients; i++)
			printf("%d ; %s\n", clients[i].client_code, clients[i].name);
	}

	free(clients);
	exit(0);
}

int ReadClients(CLIENT** v, char* filename)
{
	FILE* fp;
	int size = 0;
	
	if ((fp = fopen(filename, "rt")) == NULL)
		return(-1);
	
	while (!feof(fp))
	{
		if ((*v = (CLIENT*)realloc(*v, sizeof(CLIENT) * (size + 1))) == NULL)
			return(-2);
		fscanf(fp, "%d;%[^\n]\n", &((*v + size)->client_code), (*v + size)->name);
		size++;
	}
	
	fclose(fp);
	return(size);
}
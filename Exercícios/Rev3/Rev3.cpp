#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;

BOOLEAN MemoryAlloc(int*** v, int size);
void ReadArray(int** v, int size);
void ReadInteger(int* x);

int main(void)
{
	int** v = NULL;
	int size, i;
	setlocale(LC_ALL, "");
	printf("Dimensão do vector: ");
	if(scanf("%d", &size))
	{
		if (MemoryAlloc(&v, size))
		{
			ReadArray(v, size);
			for (i = 0; i < size; i++)
				printf("V[%d] - %d\n", i, **(v + i));
			for (i = 0; i < size; i++)
				free(*(v + i));
			free(v);
		}
		else
			printf("ERRO na alocação de memória");
	}
	else
		printf("ERRO na dimensão do vetor");
	return(0);
}

BOOLEAN MemoryAlloc(int*** v, int size)
{
	int i, j;
	if ((*v = (int**)malloc(size * sizeof(int*))) == NULL)
		return(FALSE);
	for (i = 0; i < size; i++)
		if ((*(*v + i) = (int*)malloc(sizeof(int))) == NULL)
		{
			for (j = i - 1; j >= 0; j--)
				free(*(*v + i));
			return(FALSE);
		}
	return(TRUE);
}

void ReadArray(int** v, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("v[%d]: ", i);
		ReadInteger(*(v + i));
	}
}
void ReadInteger(int* x)
{
	printf("Introduza um inteiro: ");
	if (!scanf("%d", x))
	{
		printf("ERRO no inteiro introduzido\n");
	}
}
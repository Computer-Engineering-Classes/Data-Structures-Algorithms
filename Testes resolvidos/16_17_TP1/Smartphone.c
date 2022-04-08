#include "Smartphone.h"

void ShowSmartphone(SMARTPHONE* smartphone)
{
	printf("\n%s | %s | %lf | %d\n", smartphone->marca, smartphone->modelo,
		smartphone->preco, smartphone->stock);
}

void ReadK(SMARTPHONE* smartphone)
{
	printf("Marca: ");
	scanf("%[^\n]%*c", smartphone->marca);
	printf("Modelo: ");
	scanf("%[^\n]%*c", smartphone->modelo);
	printf("Preco: ");
	scanf("%f%*c", &smartphone->preco);
	printf("Stock: ");
	scanf("%d%*c", &smartphone->stock);
}

STATUS AddSmartphone(LIST* list)
{
	SMARTPHONE* smartphone;
	smartphone = malloc(sizeof(SMARTPHONE));
	puts("Novo smartphone:");
	ReadK(smartphone);
	if (InsertIni(list, smartphone) == NULL)
		return ERROR;
	return OK;
}

void ValorTotal(LIST list)
{
	float total = 0.0f;
	while (list != NULL)
	{
		SMARTPHONE* smartphone = DATA(list);
		total += smartphone->preco * smartphone->stock;
	}
	printf("Valor total: %f\n", total);
}

STATUS ReadFile(LIST* list, const char* name_file)
{
	FILE* fp;
	SMARTPHONE smartphone, * ptr;
	if ((fp = fopen(name_file, "r")) != NULL) {
		while (!feof(fp)) {
			fscanf(fp, "%[^;];%[^;];%f;%d\n", smartphone.marca, smartphone.modelo, &smartphone.preco, &smartphone.stock);
			if (((ptr = malloc(sizeof(SMARTPHONE))) != NULL) && (InsertIni(list, ptr) != NULL))
			{
				strcpy(ptr->marca, smartphone.marca);
				strcpy(ptr->modelo, smartphone.modelo);
				ptr->preco = smartphone.preco;
				ptr->stock = smartphone.stock;
			}
			else
			{
				fclose(fp);
				return ERROR;
			}
		}
		fclose(fp);
		return OK;
	}
	else
		return ERROR;
}

void DelStockZero(LIST* list)
{
	LIST prev = NULL, tmp = NULL;
	while (*list != NULL && ((SMARTPHONE*)DATA(*list))->stock == 0)
	{
		tmp = NEXT(*list);
		free(DATA(*list));
		free(*list);
		*list = tmp;
	}
	if (*list != NULL)
	{
		prev = *list;
		tmp = NEXT(*list);
		while (tmp != NULL)
		{
			SMARTPHONE* smartphone = DATA(tmp);
			if (smartphone->stock == 0)
			{
				NEXT(prev) = NEXT(tmp);
				free(DATA(tmp));
				free(tmp);
				tmp = prev;
			}
			prev = tmp;
			tmp = NEXT(tmp);
		}
	}
}
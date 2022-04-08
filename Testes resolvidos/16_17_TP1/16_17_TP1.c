#include "Smartphone.h"

int main(int argc, char* argv[])
{
	LIST list = NULL;
	
	ReadFile(&list, "smartphones.txt");	
	ShowLista(list, &ShowSmartphone);
	
	DelStockZero(&list);	
	printf("\n----------------\n");
	ShowLista(list, &ShowSmartphone);

	return 0;
}
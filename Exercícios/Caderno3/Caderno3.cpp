#include "BinaryTree.h"

#include <stdbool.h>

int main()
{
	BTREE BT;
	BTREE_NODE* node;
	int opcao, num;
	int x[] = { 37, -43, 35, -65, 89, 6, 77, -35, -11, 41, -29, 56, -61, 42, 51,
		84, -53, -68, 43, -30, -46, 63, 0, -18, -54, 4, -91, 70, 53, -72, 38, 32, 8,
		98, -81, -76, -17, -94, -77, -14, -51, -41, -24, 90, 5, 22, -4, -82, -64, 23 };
	int y[] = { 10,25,36,2,17,4,44,27,2,1 };
	if (initBTree(&BT) == ERROR)
		exit(ERROR);
	for (int i = 0; i < 10; i++)
		insertIntBST(&BT, &y[i]);
	while (true)
	{
		printf("\nMenu:");
		printf("\n1 - Inorder");
		printf("\n2 - Preorder");
		printf("\n3 - Postorder");
		printf("\n4 - Numero de nos");
		printf("\n5 - Numero de folhas");
		printf("\n6 - Nivel de no");
		printf("\n7 - Encontrar no");
		printf("\n8 - Profundidade da arvore");
		printf("\n9 - Imprimir arvore");
		printf("\nOpcao: ");
		if (scanf(" %d", &opcao) == EOF) break;
		switch (opcao)
		{
		case 1:
			inOrderTreeWalk(BT);
			break;
		case 2:
			preOrderTreeWalk(BT);
			break;
		case 3:
			postOrderTreeWalk(BT);
			break;
		case 4:
			printf("\nNo nos: %d\n", NoBTNodes(BT));
			break;
		case 5:
			printf("\nNo folhas: %d\n", NoBTLeaves(BT));
			break;
		case 6:
			printf("No: ");
			scanf("%d", &num);
			printf("\nProfundidade de %d (BST): %d\n", num, LevelBSTNode(BT, num));
			printf("\nProfundidade de %d (BT): %d\n", num, LevelBTNode(BT, num));
			break;
		case 7:
			printf("No: ");
			scanf("%d", &num);
			node = findAgeBTNode(BT, num);
			break;
		case 8:
			printf("\nProfundidade da arvore: %d\n", DepthBT(BT));
			break;
		case 9:
			break;
		}
	}
	return 0;
}

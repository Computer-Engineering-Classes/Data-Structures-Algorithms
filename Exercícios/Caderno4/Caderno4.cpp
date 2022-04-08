#include "BinaryTree.h"

int main(void)
{
	BTREE Btree;
	void* players[STAGES];
	char file_name[MAX_NAME];
	if (ReadPlayersFromFile(players, "tournament.txt") == OK)
	{
		Btree = CreateBtree(players, 0, STAGES);
		ShowPlayers(Btree);
		printf("\nNo eliminatorias: %d\n", NoEliminatorias(Btree));
		ShowJogos(Btree);
		ShowVencedor(Btree);
		BtreeFree(Btree);
	}
	else
		printf("ERRO na leitura do ficheiro\n");
	system("pause");
	return 0;
}
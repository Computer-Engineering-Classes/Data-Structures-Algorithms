#include "Estacao.h"
#include "List.h"
#include <Windows.h>

char Menu();

int main(int argc, char* argv[])
{
    LIST Linhas[NO_LINHAS] = { NULL };
    SetConsoleOutputCP(CP_UTF8);
    LerLinhas(Linhas);
    while (true)
    {
        char opcao = Menu();
        switch (opcao)
        {
        case 'a':
            AtivarEstacao(Linhas);
            break;
        case 'b':
            AdicionarEstacao(Linhas);
            break;
        case 'c':
            EliminarEstacao(Linhas);
            break;
        case 'd':
            GuardarLinhas(Linhas);
            break;
        case 'e':
            CustoViagem(Linhas);
            break;
        case 'f':
            MostrarLinhas(Linhas);
            break;
        case 'g':
            GuardarLinhas(Linhas);
            return 0;
        default:
            printf("Opcao invalida.\n");
        }
    }
    return 0;
}

char Menu()
{
    char opcao;
    printf("Menu:\n");
    printf("\ta) Ativar estacao\n");
    printf("\tb) Adicionar estacao\n");
    printf("\tc) Eliminar estacao\n");
    printf("\td) Guardar em ficheiro\n");
    printf("\te) Custo de uma viagem\n");
    printf("\tf) Mostrar linhas\n");
    printf("\tg) Sair\n");
    printf("Opcao: ");
    scanf("%c%*c", &opcao);
    return opcao;
}
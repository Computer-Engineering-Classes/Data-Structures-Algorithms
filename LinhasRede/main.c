#include "Estacao.h"
#include <Windows.h>

char Menu();

int main(int argc, char* argv[])
{
    LIST Linhas[NO_LINHAS] = { NULL };
    SetConsoleOutputCP(CP_UTF8);
    ReadLinhas(Linhas);
    while (true)
    {
        char opcao = Menu();
        switch (opcao)
        {
        case 'a':
            ActEstacao(Linhas);
            break;
        case 'b':
            AddEstacao(Linhas);
            break;
        case 'c':
            AddPosEstacao(Linhas);
            break;
        case 'd':
            DelEstacao(Linhas);
            break;
        case 'e':
            SaveLinhas(Linhas);
            break;
        case 'f':
            CustoViagem(Linhas);
            break;
        case 'g':
            ShowLinhas(Linhas);
            break;
        case 'h':
            SaveLinhas(Linhas);
            return 0;
        default:
            puts("Opção inválida.");
        }
    }
    return 0;
}

char Menu()
{
    char opcao;
    puts("Menu:");
    puts("\ta) Ativar estação");
    puts("\tb) Adicionar estação");
    puts("\tc) Adicionar estação, numa certa posição");
    puts("\td) Eliminar estação");
    puts("\te) Guardar em ficheiro");
    puts("\tf) Custo de uma viagem");
    puts("\tg) Mostrar linhas");
    puts("\th) Sair");
    printf("Opção: ");
    scanf("%c%*c", &opcao);
    return opcao;
}
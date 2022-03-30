#include "Estacao.h"

/*
* Ler dados de estação a partir de ficheiro
*/
ESTACAO* ReadEstacao(FILE* fp)
{
    int ativa, no;
    char buffer[MAX_BUF];
    ESTACAO* est = malloc(sizeof(ESTACAO));
    fgets(buffer, MAX_BUF, fp);
    sscanf(buffer, "%[^;];%f;%d;%d;",
        est->desig, &est->custo, &ativa, &no);
    est->ativa = ativa;
    est->no = no;
    return est;
}
/*
* Ler dados de estação a partir do teclado
*/
ESTACAO* ReadKEstacao()
{
    ESTACAO* est;
    est = malloc(sizeof(ESTACAO));
    printf("Designação: ");
    scanf("%[^\n]", est->desig);
    printf("Custo: ");
    scanf("%f", &est->custo);
    printf("Ativa? (1/0): ");
    scanf("%d", &est->ativa);
    printf("Nó de ligação? (1/0): ");
    scanf("%d", &est->no);
    return est;
}
/*
* Salvar dados de estação em ficheiro
*/
void SaveEstacao(FILE* fp, ESTACAO* est)
{
    fprintf(fp, "%s;%f;%d;%d;\n",
        est->desig, est->custo, est->ativa, est->no);
}
/*
* Inicializar linhas da rede
*/
void InitLinhas(LIST* Linhas)
{
    for (int i = 0; i < NO_LINHAS; i++)
    {
        initList(&Linhas[i]);
    }
}
/*
* Mostrar linhas da rede na consola
*/
void ShowLinhas(LIST* Linhas)
{
    for (int i = 0; i < NO_LINHAS; i++)
    {
        ShowValues(Linhas[i]);
        puts("\n");
    }
}
/*
* Ler linhas da rede a partir dos ficheiros
*/
void ReadLinhas(LIST* Linhas)
{
    FILE* fp = NULL;
    char filename[MAX];
    for (int i = 0; i < NO_LINHAS; i++)
    {
        sprintf(filename, ".\\Linhas\\Linha%d.txt", i + 1);
        fp = fopen(filename, "r");
        while (!feof(fp))
        {
            ESTACAO* est = ReadEstacao(fp);
            InsertEnd(&Linhas[i], est);
        }
        fclose(fp);
    }
}
/*
* Guardar todas as linhas da rede nos ficheiros de texto correspondentes.
*/
void SaveLinhas(LIST* Linhas)
{
    FILE* fp = NULL;
    char filename[MAX];
    for (int i = 0; i < NO_LINHAS; i++)
    {
        sprintf(filename, ".\\Linhas\\Linha%d.txt", i + 1);
        fp = fopen(filename, "w");
        if (!emptyList(Linhas[i]))
        {
            LIST_NODE* tmp = Linhas[i];
            while (tmp != NULL)
            {
                ESTACAO* est = DATA(tmp);
                SaveEstacao(fp, est);
                tmp = NEXT(tmp);
            }
        }
        fclose(fp);
    }
}
/*
* Tornar ativa/inativa uma estação
* Designação deve ser lida através do teclado
*/
STATUS ActEstacao(LIST* Linhas)
{
    LIST_NODE* node;
    char desig[MAX];
    printf("Designação: ");
    scanf("%[^\n]%*c", desig);
    node = FindEstacao(Linhas, desig);
    if (node != NULL)
    {
        ESTACAO* est = DATA(node);
        est->ativa = !est->ativa;
        return OK;
    }
    return ERROR;
}
/*
* Acrescentar uma estação a uma linha
* Número deve ser lido através do teclado bem como todos os dados dessa estação
*/
STATUS AddEstacao(LIST* Linhas)
{
    int no_linha;
    ESTACAO* est;
    printf("N.º linha: ");
    scanf("%d%*c", &no_linha);
    if (no_linha > 0 && no_linha < 6)
    {
        est = ReadKEstacao();
        return InsertEnd(&Linhas[no_linha - 1], est);
    }
    return ERROR;
}
/*
* Acrescentar uma estação a uma linha, numa determinada posição
*/
STATUS AddPosEstacao(LIST* Linhas)
{
    int no_linha;
    ESTACAO* est;
    printf("N.º linha: ");
    scanf("%d%*c", &no_linha);
    if (no_linha > 0 && no_linha < 6)
    {
        est = ReadKEstacao();
        int pos;
        printf("Posição da linha (0..n-1): ");
        scanf("%d%*c", &pos);
        return InsertPos(&Linhas[no_linha - 1], est, pos);
    }
    return ERROR;
}
/*
* Eliminar uma estação de uma determinada linha
* O número da linha e a designação devem ser lidas através do teclado
*/
STATUS DelEstacao(LIST* Linhas)
{
    char desig[MAX];
    int no_linha;
    printf("N.º linha: ");
    scanf("%d%*c", &no_linha);
    if (no_linha < 1 || no_linha > 5)
    {
        return ERROR;
    }
    printf("Designação: ");
    scanf("%[^\n]%*c", desig);
    ESTACAO* est = DATA(Linhas[no_linha - 1]);
    if (strcmp(est->desig, desig) == 0)
    {
        RemoveIni(&Linhas[no_linha - 1]);
        return OK;
    }
    LIST_NODE* tmp = Linhas[no_linha - 1];
    while (NEXT(tmp) != NULL)
    {
        est = DATA(NEXT(tmp));
        if (strcmp(est->desig, desig) == 0)
        {
            LIST_NODE* node = NEXT(NEXT(tmp));
            free(DATA(NEXT(tmp)));
            free(NEXT(tmp));
            NEXT(tmp) = node;
            return OK;
        }
        tmp = NEXT(tmp);
    }
    return ERROR;
}
/*
* Calcular o custo de uma viagem
* Devem ser lidas as estações de origem e de destino através do teclado
*/
float CustoViagem(LIST* Linhas)
{
    LIST_NODE* node;
    float custo = 0.0f;
    char origem[MAX], destino[MAX];
    printf("Origem: ");
    scanf("%[^\n]%*c", origem);
    printf("Destino: ");
    scanf("%[^\n]%*c", destino);
    if (strcmp(origem, destino) == 0) return 0.0f;
    node = FindEstacao(Linhas, origem);
    ESTACAO* est = DATA(node);
    while (NEXT(node) != NULL && strcmp(est->desig, destino) != 0)
    {
        node = NEXT(node);
        est = DATA(node);
        custo += est->custo;
    }
    return custo;
}
/*
* Procurar uma estação nas linhas da rede
* Saida: apontador do nó em que se encontra a estação
*/
LIST_NODE* FindEstacao(LIST* Linhas, char* desig)
{
    ESTACAO* est = NULL;
    for (int i = 0; i < NO_LINHAS; i++)
    {
        LIST_NODE* tmp = Linhas[i];
        while (tmp != NULL)
        {
            est = DATA(tmp);
            if (strcmp(est->desig, desig) == 0)
            {
                return tmp;
            }
        }
    }
    return NULL;
}

#include "Estacao.h"

/*
* Ler dados de esta��o a partir de ficheiro
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
* Ler dados de esta��o a partir do teclado
*/
ESTACAO* ReadKEstacao()
{
    ESTACAO* est;
    est = malloc(sizeof(ESTACAO));
    printf("Designa��o: ");
    scanf("%[^\n]", est->desig);
    printf("Custo: ");
    scanf("%f", &est->custo);
    printf("Ativa? (1/0): ");
    scanf("%d", &est->ativa);
    printf("N� de liga��o? (1/0): ");
    scanf("%d", &est->no);
    return est;
}
/*
* Salvar dados de esta��o em ficheiro
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
void MostrarLinhas(LIST* Linhas)
{
    for (int i = 0; i < NO_LINHAS; i++)
    {
        ShowValues(Linhas[i]);
        printf("\n\n");
    }
}
/*
* Ler linhas da rede a partir dos ficheiros
*/
void LerLinhas(LIST* Linhas)
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
void GuardarLinhas(LIST* Linhas)
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
* Tornar ativa/inativa uma esta��o
* Designa��o deve ser lida atrav�s do teclado
*/
STATUS AtivarEstacao(LIST* Linhas)
{
    LIST_NODE* node;
    char desig[MAX];
    printf("Designacao: ");
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
* Acrescentar uma esta��o a uma linha
* N�mero deve ser lido atrav�s do teclado bem como todos os dados dessa esta��o
*/
STATUS AdicionarEstacao(LIST* Linhas)
{
    int no_linha;
    ESTACAO* est;
    printf("N.� linha: ");
    scanf("%d%*c", &no_linha);
    if (no_linha > 0 && no_linha < 6)
    {
        est = ReadKEstacao();
        InsertEnd(&Linhas[no_linha - 1], est);
        return OK;
    }
    return ERROR;
}
/*
* Eliminar uma esta��o de uma determinada linha
* O n�mero da linha e a designa��o devem ser lidas atrav�s do teclado
*/
STATUS EliminarEstacao(LIST* Linhas)
{
    char desig[MAX];
    int no_linha;
    printf("N.� linha: ");
    scanf("%d%*c", &no_linha);
    if (no_linha < 1 || no_linha > 5)
    {
        return ERROR;
    }
    printf("Designacao: ");
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
* Devem ser lidas as esta��es de origem e de destino atrav�s do teclado
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
* Procurar uma esta��o nas linhas da rede
* Saida: apontador do n� em que se encontra a esta��o
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

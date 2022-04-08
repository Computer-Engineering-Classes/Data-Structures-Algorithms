#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

typedef enum _STATUS { ERROR, OK } STATUS;
typedef enum _BOOLEAN { FALSE, TRUE } BOOLEAN;

#define MAX 20

typedef struct _LIVRO {
    char     autor[MAX], titulo[MAX];
    int      stock, iva, paginas;
    float    preco;
}LIVRO;

typedef struct _LIST_NODE
{
    void* data;
    struct _LIST_NODE* next;
} LIST_NODE;

typedef LIST_NODE* LIST;

#define DATA(node) ((node)->data)
#define NEXT(node) ((node)->next)

STATUS ReadList(LIST* list);
STATUS InsertIni(LIST* list, void* data);
LIST_NODE* NewNode(void* data);

int main()
{
    LIST lista = NULL;
    if (ReadList(&lista))
    {
        
    }
    float min = ArtigoMaisBarato(lista);
    return 1;
}

void EliminarEnd(LIST* list)
{
    LIST tmp, prev;
    if (*list != NULL)
    {
        if ((*list)->next == NULL)
        {
            free((*list)->data);
            free(*list);
            *list = NULL;
        }
        else
        {
            tmp = *list;
            while (tmp->next != NULL)
            {
                prev = tmp;
                tmp = tmp->next;
            }
            free(tmp->data);
            free(tmp);
            prev->next = NULL;
        }
    }
}

float ArtigoMaisBarato(LIST list)
{
    float menor_preco = 0;
    int pos = 1, pos_atual = 1;
    if (list != NULL)
    {
        pos = 1;
        menor_preco = ((LIVRO*)list->data)->preco;
        while (list != NULL)
        {
            if (((LIVRO*)list->data)->preco < menor_preco)
            {
                pos = pos_atual;
                menor_preco = ((LIVRO*)list->data)->preco;
            }
            ++pos_atual;
            list = list->next;
        }
        printf("\nPosicao do livro mais barato: %d", pos);
        return menor_preco;
    }
    return(-1);
}

STATUS ReadList(LIST* list)
{
    FILE* fp;
    LIVRO* livro;
    if ((fp = fopen("input.txt", "r")) != NULL)
    {
        for (int i = 0; i < 789; i++)
        {
            if ((livro = (LIVRO*)malloc(sizeof(LIVRO))) != NULL)
            {
                fscanf(fp, "%[^;];%[^;];%d;%d;%d;%f\n", livro->autor, livro->titulo, &livro->stock, &livro->iva, &livro->paginas, &livro->preco);
                InsertIni(list, livro);
            }
            else
                return ERROR;
        }
        fclose(fp);
        return OK;
    }
    return ERROR;
}

STATUS InsertIni(LIST* list, void* data)
{
    LIST_NODE* new_node;
    if ((new_node = NewNode(data)) != NULL)
    {
        NEXT(new_node) = *list;
        *list = new_node;
        return STATUS::OK;
    }
    return STATUS::ERROR;
}

LIST_NODE* NewNode(void* data)
{
    LIST_NODE* new_node;
    if ((new_node = (LIST_NODE*)malloc(sizeof(LIST_NODE))) != NULL)
    {
        DATA(new_node) = data;
        NEXT(new_node) = NULL;
    }
    return(new_node);
}
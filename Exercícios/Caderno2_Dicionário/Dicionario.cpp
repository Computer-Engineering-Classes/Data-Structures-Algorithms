#include "Dicionario.h"

unsigned long hash(char* str) 
{
    unsigned long hash = 0;
    int c;
    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;
    return hash % TAMARRAY;
}

unsigned long hash(const char* str) 
{
    unsigned long hash = 0;
    int c;
    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;
    return hash % TAMARRAY;
}

Dictionary newDictionary() 
{
    // Creates a new HashTable
    _Dictionary* table = (_Dictionary*)malloc(sizeof(_Dictionary));
    table->size = TAMARRAY;
    table->count = 0;
    if ((table->items = (DicItem**)calloc(table->size, sizeof(DicItem*))) != NULL)
        for (int i = 0; i < table->size; i++)
            table->items[i] = NULL;
    else {
        printf("hehehe foi demais!!!");
        exit(-1);
    }
    return table;
}

DicItem* create_item(char* key, void* data) {
    // Creates a pointer to a new hash table item
    DicItem* item = (DicItem*)malloc(sizeof(DicItem));
    item->key = (char*)malloc(sizeof(key) * strlen(key));
    item->data = NULL;
    strcpy(item->key, key);
    item->data = data;
    return item;
}

DicItem* create_item(const char* key, void* data) {
    // Creates a pointer to a new hash table item
    DicItem* item = (DicItem*)malloc(sizeof(DicItem));
    item->key = (char*)malloc(sizeof(key) * strlen(key));
    item->data = NULL;
    strcpy(item->key, key);
    item->data = data;
    return item;
}

void handle_collision(Dictionary table, DicItem* item) 
{
}

//add(Dictionary dictionary, char* key, void* data, void (*deleteFunctionDictionary)(void* data))
void add(Dictionary table, char* key, void* data, void (*func)(void* data)) 
{
    // Create the item    
    DicItem* item = create_item(key, data);
    // Compute the index
    int index = hash(key);
    DicItem* current_item = table->items[index];
    if (current_item == NULL) 
    {
    // Key does not exist.        
        if (table->count == table->size) 
        {
        // Hash Table Full            
            printf("Insert Error: Hash Table is full\n");
            deleteItem(item, func);
            return;
        }
    // Insert directly        
        table->items[index] = item;
        table->count++;
    }
    else 
    {
    // Scenario 1: We only need to update value        
        if (strcmp(current_item->key, key) == 0) 
        {
            table->items[index]->data = data;
            deleteItem(item, func);
            return;
        }
        else 
        {
        // Scenario 2: Collision            // We will handle case this a bit later            
            handle_collision(table, item);
            return;
        }
    }
}

//add(Dictionary dictionary, const char* key, void* data, void (*deleteFunctionDictionary)(void* data))
void add(Dictionary table, const char* key, void* data, void (*func)(void* data)) 
{
    // Create the item    
    DicItem* item = create_item(key, data);
    // Compute the index
    int index = hash(key);
    DicItem* current_item = table->items[index];
    if (current_item == NULL) 
    {
    // Key does not exist.
        if (table->count == table->size)
        {
        // Hash Table Full
            printf("Insert Error: Hash Table is full\n");
            deleteItem(item, func);
            return;
        }
        // Insert directly
        table->items[index] = item;
        table->count++;
    }
    else 
    {
    // Scenario 1: We only need to update value
        if (strcmp(current_item->key, key) == 0) 
        {
            table->items[index]->data = data;
            deleteItem(item, func);
            return;
        }
        else 
        {
        // Scenario 2: Collision
        // We will handle case this a bit later
            handle_collision(table, item);
            return;
        }
    }
}

DicItem* search(Dictionary table, char* key) 
{
    // Searches the key in the hashtable
    // and returns NULL if it doesn't exist
    int index = hash(key);
    DicItem* item = table->items[index];
    // Ensure that we move to a non NULL item
    if (item != NULL) 
        if (strcmp(item->key, key) == 0)
            return item;
    return NULL;
}

DicItem* search(Dictionary table, const char* key) {
    // Searches the key in the hashtable
    // and returns NULL if it doesn't exist
    int index = hash(key);
    DicItem* item = table->items[index];
    // Ensure that we move to a non NULL item
    if (item != NULL) 
        if (strcmp(item->key, key) == 0)
            return item;
    return NULL;
}

void print(Dictionary table, void (*func)(void* data)) 
{
    printf("\n-------------------\n");
    if (table == NULL || table->count == 0) 
    {
        printf("\nDicionario Vazio.\n");
        return;
    }
    for (int i = 0; i < table->size; i++) 
    {
        if (table->items[i]) 
        {
            printf("Index:%d, Key:%s, Value:", i, table->items[i]->key);
            func((table->items[i]->data));
        }
    }
    printf("-------------------\n");
}

int size(Dictionary table) 
{
    return table->count;
}

STATUS deleteItem(Dictionary table, char* key, void (*func)(void* data)) 
{
    if (table == NULL)
        return ERROR;
    int index = hash(key);
    DicItem* item = table->items[index];
    // Frees an item
    free(item->key);
    if (item->data != NULL) 
    {
        func(item->data);
        free(item->data);
    }
    free(item);
    table->items[index] = NULL;
    return OK;
}

STATUS deleteItem(DicItem* item, void (*func)(void* data)) 
{
    if (item == NULL)
        return ERROR;
    // Frees an item
    free(item->key);
    if (item->data != NULL) {
        func(item->data);
        free(item->data);
    }
    free(item);
    return OK;
}

void emptyDictionary(Dictionary table, void (*func)(void* data)) 
{
    if (table == NULL || table->count == 0)
        return;
    // Frees the dictionary
    DicItem* item = NULL;
    for (int i = 0; i < table->size; i++) {
        item = table->items[i];
        if (item != NULL) {
            deleteItem(item, func);
            table->items[i] = NULL;
        }
    }
    table->count = 0;
}

void deleteDictionary(Dictionary table, void (*func)(void* data)) 
{
    if (table == NULL || table->count == 0)
        return;
    // Frees the dictionary
    DicItem* item = NULL;
    for (int i = 0; i < table->size; i++) {
        item = table->items[i];
        if (item != NULL)
            deleteItem(item, func);
    }
    free(table->items);
    free(table);
}
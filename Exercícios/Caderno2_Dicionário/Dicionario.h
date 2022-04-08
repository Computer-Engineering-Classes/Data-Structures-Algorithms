#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAMARRAY 0xffff // 65535
#define DATA(value) ((value)->data)

typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _LIST_LOCATION { LIST_START, LIST_END } LIST_LOCATION;
typedef enum _STATUS { OK, ERROR } STATUS;

struct DicItem 
{
    char* key;
    void* data;
};

struct _Dictionary {
    // Contains an array of pointers    // to items
    DicItem** items;
    unsigned int size;
    unsigned int count;
};
typedef struct _Dictionary* Dictionary;

//functions
char* tostring(int num);
unsigned long hash(char* str);
unsigned long hash(const char* str);
Dictionary newDictionary();
void handle_collision(Dictionary table, DicItem* item);
DicItem* create_item(char* key, void* data);
DicItem* create_item(const char* key, void* data);
void add(Dictionary table, char* key, void* data, void (*func)(void* data));
void add(Dictionary table, const char* key, void* data, void (*func)(void* data));
DicItem* search(Dictionary table, char* key);
DicItem* search(Dictionary table, const char* key);
void print(Dictionary table, void (*func)(void* data));
int size(Dictionary table);
STATUS deleteItem(Dictionary table, char* key, void (*func)(void* data));
STATUS deleteItem(DicItem* item, void (*func)(void* data));
void emptyDictionary(Dictionary table, void (*func)(void* data));
void deleteDictionary(Dictionary table, void (*func)(void* data));
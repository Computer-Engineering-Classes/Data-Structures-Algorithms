#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME 50
#define STAGES 15

typedef struct _PLAYER
{
	char name[MAX_NAME];
	int sets;
}PLAYER;
#pragma once

#include <stdio.h>

typedef enum ObjectType
{
	EMPTY,
	WALL,
	ROCK,
	INVALID_OBJECT,
} ObjectType;

typedef struct Object
{
	ObjectType type;
	wchar_t rendering_character;
} Object;
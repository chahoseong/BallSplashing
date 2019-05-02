#pragma once

#include <stdio.h>

enum ObjectType
{
	GOAL = -1,
	EMPTY = 0,
	WALL = 1,
	ROCK = 2,
};

//typedef struct _Object
//{
//	
//} Object;

wchar_t* LoadStage(const char* name);
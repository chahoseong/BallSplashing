#pragma once

/*
Types
*/
typedef struct _Vector2
{
	float x, y;
} Vector2;

/*
Global Variables

*/

/*
Functions
*/
int Startup();
void Shutdown();
void GameLoop();

const char* KeyState();

void Gotoxy(int x, int y);
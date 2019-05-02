#pragma once

#include "type.h"
#include <stdio.h>

void InitGraphics(int width, int height);
void ReleaseGraphics();

void DrawObject(wchar_t character, Vector2 position);
void PresentGraphics();

Vector2 GetWindowSize();

void GotoConsoleCursor(int x, int y);
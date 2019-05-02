#pragma once

#include <stdio.h>

struct Renderer;
typedef struct Renderer Renderer;

Renderer* CreateRenderer(int width, int height);
void DestroyRenderer(Renderer* renderer);

int GetRenderSize(Renderer* renderer, int* width, int* height);

void RenderDraw(Renderer* renderer, wchar_t character, int x, int y);
void RenderPresent(Renderer* renderer);

void GotoConsoleCursor(int x, int y);
#pragma once

#include <stdio.h>

typedef enum TextAlignment
{
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT,
} TextAlignment;

struct Renderer;
typedef struct Renderer Renderer;

Renderer* CreateRenderer(int width, int height);
void DestroyRenderer(Renderer* renderer);

int GetRenderSize(Renderer* renderer, int* width, int* height);
void SetRenderDrawColor(Renderer* renderer, int foreground, int background);

void RenderClear(Renderer* renderer, wchar_t character);
void RenderDraw(Renderer* renderer, wchar_t character, int x, int y);
void RenderDrawText(Renderer* renderer, const wchar_t* text, int length, int x, int y, TextAlignment alignment);
void RenderPresent(Renderer* renderer);

void GotoConsoleCursor(int x, int y);
void SetDrawColor(int foreground, int background);
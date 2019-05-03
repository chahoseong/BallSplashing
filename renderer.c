#include "renderer.h"

#include <locale.h>
#include <stdio.h>
#include <Windows.h>

typedef struct Pixel
{
	wchar_t ch;
	WORD color;
} Pixel;

typedef struct Renderer
{
	Pixel* buffer;
	WORD draw_color;
	int width;
	int height;
} Renderer;

/*
Internal Functions
*/
void HideConsoleCursor()
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void GotoConsoleCursor(int x, int y)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

/*
Renderer Functions
*/
Renderer* CreateRenderer(int width, int height)
{
	Renderer* renderer = (Renderer*)malloc(sizeof(Renderer));
	if (!renderer)
		return NULL;

	renderer->buffer = (Pixel*)malloc(sizeof(Pixel) * width * height);
	if (!renderer->buffer)
		return NULL;

	renderer->width = width;
	renderer->height = height;

	HideConsoleCursor();
	memset(renderer->buffer, 0, sizeof(Pixel) * width * height);

	return renderer;
}

void DestroyRenderer(Renderer* renderer)
{
	free(renderer->buffer);
	free(renderer);
}

int GetRenderSize(Renderer* renderer, int* width, int* height)
{
	if (!renderer)
		return 0;

	*width = renderer->width;
	*height = renderer->height;

	return 1;
}

void SetRenderDrawColor(Renderer* renderer, int foreground, int background)
{
	renderer->draw_color = (background << 4) | foreground;
}

void RenderClear(Renderer* renderer, wchar_t character)
{
	for (int y = 0; y < renderer->height; ++y)
	{
		for (int x = 0; x < renderer->width; ++x)
			renderer->buffer[y * renderer->width + x].ch = character;
	}
}

void RenderDraw(Renderer* renderer, wchar_t character, int x, int y)
{
	int index = y * renderer->width + x;

	renderer->buffer[index].ch = character;
	renderer->buffer[index].color = renderer->draw_color;
}

void RenderPresent(Renderer* renderer)
{
	GotoConsoleCursor(0, 0);

	for (int y = 0; y < renderer->height; ++y)
	{
		for (int x = 0; x < renderer->width; ++x)
		{
			int index = y * renderer->width + x;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), renderer->buffer[index].color);
			printf("%2lc", renderer->buffer[index].ch);
		}
		putchar('\n');
	}
}

void ResizeWindow(int width, int height)
{
	char command[64];
	sprintf_s(command, 64, "mode con: cols=%d lines=%d", width, height);
	system(command);
}
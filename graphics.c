#include "graphics.h"

#include <locale.h>
#include <stdio.h>
#include <Windows.h>

static wchar_t* frame_buffer;
static Vector2 frame_buffer_size;

void HideConsoleCursor();
void ResizeWindow(int width, int height);
void CreateFrameBuffer(int width, int height);

void InitGraphics(int width, int height)
{
	setlocale(LC_ALL, "");

	HideConsoleCursor();
	CreateFrameBuffer(width, height);
	ResizeWindow(width, height);
}

void ReleaseGraphics()
{
	free(frame_buffer);
}

void DrawObject(wchar_t object, Vector2 position)
{
	// 버퍼의 범위를 벗어난 위치에 들어오면 그리지 않는다.
	if (position.x < 0 || position.x > frame_buffer_size.x || position.y < 0 || position.y > frame_buffer_size.y)
		return;

	frame_buffer[(int)(position.y * frame_buffer_size.x + position.x)] = object;
}

void PresentGraphics()
{
	GotoConsoleCursor(0, 0);
	for (int y = 0; y < frame_buffer_size.y; ++y)
	{
		for (int x = 0; x < frame_buffer_size.x; ++x)
			printf("%lc", frame_buffer[(int)(y * frame_buffer_size.x + x)]);
	}
}

Vector2 GetWindowSize()
{
	return frame_buffer_size;
}

void GotoConsoleCursor(int x, int y)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void HideConsoleCursor()
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void ResizeWindow(int width, int height)
{
	char command[64];
	sprintf_s(command, 64, "mode con: cols=%d lines=%d", width, height);
	system(command);
}

void CreateFrameBuffer(int width, int height)
{
	int size = sizeof(wchar_t) * width * height;
	frame_buffer = (wchar_t*)malloc(size);

	if (!frame_buffer)
		return;

	memset(frame_buffer, 0, size);

	frame_buffer_size.x = width;
	frame_buffer_size.y = height;
}
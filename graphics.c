#include "graphics.h"
#include <Windows.h>

static HANDLE frame_buffer[2];
static int frame_cursor;

static int width;
static int height;

int InitGraphics(int new_width, int new_height)
{
	COORD buffer_size = { width, height };
	SMALL_RECT window_size;
	window_size.Top = 0;
	window_size.Left = 0;
	window_size.Right = width - 1;
	window_size.Bottom = height - 1;

	// front buffer
	frame_buffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	if (frame_buffer[0] == INVALID_HANDLE_VALUE)
		return 0;
	SetConsoleScreenBufferSize(frame_buffer[0], buffer_size);
	SetConsoleWindowInfo(frame_buffer[0], TRUE, &window_size);

	// back buffer
	frame_buffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	if (frame_buffer[1] == INVALID_HANDLE_VALUE)
		return 0;
	SetConsoleScreenBufferSize(frame_buffer[1], buffer_size);
	SetConsoleWindowInfo(frame_buffer[1], TRUE, &window_size);

	width = new_width;
	height = new_height;

	return 1;
}

void CloseGraphics()
{
	CloseHandle(frame_buffer[0]);
	CloseHandle(frame_buffer[1]);
}

void ClearFrameBuffer()
{
	COORD start_position = { 0, 0 };
	FillConsoleOutputCharacterA(frame_buffer, ' ', width * height, start_position, NULL);
}

void WriteFrameBuffer(char* string, int size, int x, int y)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(frame_buffer[frame_cursor], position);
	WriteFile(frame_buffer[frame_cursor], string, strlen(string), NULL, NULL);
}

void SwapFrameBuffer()
{
	SetConsoleActiveScreenBuffer(frame_buffer[frame_cursor]);
	frame_cursor != frame_cursor;
}

HANDLE CurrentFrameBuffer()
{
	return frame_buffer[frame_cursor];
}
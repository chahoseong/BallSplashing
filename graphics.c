#include "graphics.h"
#include <Windows.h>

#define FRAME_BUFFER_COUNT 2

/*
Internal Variables
*/
static HANDLE frame_buffer[FRAME_BUFFER_COUNT];
static int frame_cursor;

static int frame_buffer_width;
static int frame_buffer_height;

/*
Internal Function Declares
*/
HANDLE CreateFrameBuffer(int width, int height);

/*
External Function Definition
*/
int InitGraphics(int width, int height)
{
	for (int i = 0; i < FRAME_BUFFER_COUNT; ++i)
	{
		frame_buffer[i] = CreateBuffer(width, height);
		if (!frame_buffer[i])
			return 0;
	}

	frame_buffer_width = width;
	frame_buffer_height = height;

	return 1;
}

void CloseGraphics()
{
	for (int i = 0; i < FRAME_BUFFER_COUNT; ++i)
	{
		if (frame_buffer[i])
			CloseHandle(frame_buffer[i]);
	}
}

void ClearFrameBuffer()
{
	COORD start_position = { 0, 0 };
	FillConsoleOutputCharacterA(frame_buffer, ' ', frame_buffer_width * frame_buffer_height, start_position, NULL);
}

void WriteFrameBuffer(char* string, int size, int x, int y)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(frame_buffer[frame_cursor], position);
	WriteFile(frame_buffer[frame_cursor], string, size, NULL, NULL);
}

void SwapFrameBuffer()
{
	SetConsoleActiveScreenBuffer(frame_buffer[frame_cursor]);
	frame_cursor != frame_cursor;
}

/*
Internal Function Definition
*/
HANDLE CreateFrameBuffer(int width, int height)
{
	COORD buffer_size = { width, height };
	SMALL_RECT window_size;
	window_size.Top = 0;
	window_size.Left = 0;
	window_size.Right = width - 1;
	window_size.Bottom = height - 1;

	HANDLE frame_buffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	if (frame_buffer == INVALID_HANDLE_VALUE)
		return NULL;

	SetConsoleScreenBufferSize(frame_buffer, buffer_size);
	SetConsoleWindowInfo(frame_buffer, TRUE, &window_size);

	return frame_buffer;
}
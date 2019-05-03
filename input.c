#include "input.h"
#include <conio.h>
#include <Windows.h>

#define MAX_KEYS 256

enum KeyCode
{
	KEY_ESC = 27,
	KEY_UP = 72,
	KEY_LEFT = 75,
	KEY_RIGHT = 77,
	KEY_DOWN = 80,
	KEY_ARROW = 224,
};

static char keys[MAX_KEYS];

void PollInput()
{
	memset(keys, 0, MAX_KEYS);

	if (_kbhit())
	{
		int key = _getch();
		
		if (key == KEY_ARROW)
		{
			key = _getch();
			switch (key)
			{
			case KEY_LEFT:
				keys[VK_LEFT] = 1;
				break;
			case KEY_RIGHT:
				keys[VK_RIGHT] = 1;
				break;
			}
		}
		else
		{
			switch (key)
			{
			case KEY_ESC:
				keys[VK_ESCAPE] = 1;
				break;
			}
		}
	}
}

const char* GetKeyboard()
{
	return keys;
}
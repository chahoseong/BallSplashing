#include "input.h"
#include <conio.h>
#include <Windows.h>

#define MAX_KEYS 256

typedef enum KeyCode
{
	KEY_ESC = 27,
	KEY_UP = 72,
	KEY_PAGE_UP = 73,
	KEY_LEFT = 75,
	KEY_RIGHT = 77,
	KEY_DOWN = 80,
	KEY_PAGE_DOWN = 81,
	KEY_ARROW = 224,
} KeyCode;

static char keys[MAX_KEYS];

void PollKeys()
{
	memset(keys, 0, MAX_KEYS);

	if (_kbhit())
	{
		int key = _getch();
		
		if (key == KEY_ARROW || key == 0)
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
			case KEY_PAGE_UP:
				keys[VK_PRIOR] = 1;
				break;
			case KEY_PAGE_DOWN:
				keys[VK_NEXT] = 1;
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
			case 'r':
			case 'R':
				keys[VK_R] = 1;
				break;
			}
		}
	}
}

const char* GetKeys()
{
	return keys;
}
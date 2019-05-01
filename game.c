#include "game.h"
#include "graphics.h"
#include "timer.h"
#include "player.h"

#include <conio.h>
#include <stdio.h>
#include <Windows.h>

#define MAX_KEYS 256
#define KEY_ARROW 224
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

static Timer game_timer;
static char keys[MAX_KEYS];

static Player* player;

/*
Declare Functions
*/
void Input();
void Update();
void Render();


int Startup()
{
	player = (Player*)malloc(sizeof(Player));

	if (!InitTimer(&game_timer))
	{
		fprintf(stderr, "InitTimer() failed");
		return 0;
	}
}

void Shutdown()
{
	CloseTimer(&game_timer);
	free(player);
}

void GameLoop()
{
	ResetTimer(game_timer);

	while (1)
	{
		Input();
		Update();
		Render();
	}
}

void Input()
{
	memset(keys, 0, sizeof(keys));

	if (_kbhit())
	{
		int key = _getch();
		
		if (key == KEY_ARROW)
		{
			key = _getch();
		}
		else
		{

		}
	}
}

void Update()
{
	TickTimer(game_timer);
	float delta_time = DeltaTime(game_timer);

	UpdatePlayer(player, delta_time);
}

void Render()
{
	ClearFrameBuffer();
	RenderPlayer(player);
	SwapFrameBuffer();
}
#include "game.h"
#include "graphics.h"
#include "input.h"
#include "timer.h"
#include "stage.h"
#include "player.h"

#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include <Windows.h>


/*
Internal Variables
*/
static Timer* game_timer;
static wchar_t* stage;
static Player* player;

static int is_running;

/*
*/
static float test_timer;

/*
Declare Functions
*/
void Input();
void Update();
void Render();

int StartupGame()
{
	InitGraphics(80, 24);

	game_timer = CreateTimer();
	if (!game_timer)
	{
		fprintf(stderr, "Failed CreateTimer()");
		return 0;
	}

	stage = LoadStage("stage2.txt");

	player = CreatePlayer();
	player->max_force.x = 25;

	is_running = 1;

	return 1;
}

void ShutdownGame()
{
	DestroyPlayer(&player);
	DestroyTimer(&game_timer);
	ReleaseGraphics();
}

void RunningGame()
{
	ResetTimer(game_timer);

	while (is_running)
	{
		Input();
		Update();
		Render();
	}
}

void Input()
{
	PollInputEvent();
	
	const char* keys = GetKeys();

	InputPlayer(player, keys);
}

void Update()
{
	TickTimer(game_timer);

	UpdatePlayer(player, game_timer->delta_time);

	if (test_timer >= 1.0f)
	{
		char log[128];
		sprintf_s(log, 128, "(%f, %f)", player->curr_position.x, player->curr_position.y);
		SetConsoleTitleA(log);

		test_timer = 0.0f;
	}
	else
	{
		test_timer += game_timer->delta_time;
	}
}

void Render()
{
	RenderPlayer(player);
	PresentGraphics();
}
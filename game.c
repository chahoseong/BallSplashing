#include "game.h"
#include "renderer.h"
#include "sound.h"
#include "input.h"
#include "timer.h"

#include "type.h"
#include "stage.h"
#include "player.h"
#include "credit.h"

#include <ctype.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef enum GameState
{
	READY,
	PLAYING,
	CLEAR,
	GAME_OVER,
	ENDING,
	FATAL_ERROR,
} GameState;

typedef struct Game
{
	Renderer* renderer;
	Timer* timer;
	Stage* stage;
	Player* player;
	Credit* credit;

	GameState state;
	float update_time;
	int gravity;
	int stage_count;

	int stage_index;
	float start_delay;
	float end_delay;
	int gravity_count;

	int is_input;
	int is_running;
} Game;

int ReadConfig(Game* game);

void Input(Game* game);
void Update(Game* game, float delta_time);
void Render(Game* game);

void ReadyGame(Game* game, float delta_time);
void PlayGame(Game* game, float delta_time);
void ClearGame(Game* game, float delta_time);
void CleanGame(Game* game);

Game* CreateGame()
{
	Game* game = (Game*)malloc(sizeof(Game));
	if (!game)
		return NULL;

	return game;
}

void DestroyGame(Game* game)
{
	free(game);
}

int StartupGame(Game* game)
{
	// 확장 문자를 출력하기 위한 설정
	// LC_ALL은 모든 카테고리, ""은 현재 시스템
	setlocale(LC_ALL, "");

	game->renderer = CreateRenderer(21, 17);
	if (!game->renderer)
	{
		fprintf(stderr, "Failed CreateRenderer()");
		return 0;
	}

	game->timer = CreateTimer();
	if (!game->timer)
	{
		fprintf(stderr, "Failed CreateTimer()");
		return 0;
	}

	if (!ReadConfig(game))
	{
		fprintf(stderr, "Failed ReadConfig()");
		return 0;
	}

	game->stage = NULL;
	game->player = CreatePlayer(L'●');
	SetPlayerMaxVelocity(game->player, 1, 1);

	game->credit = CreateCredit(game->renderer, "credit.txt");

	game->state = READY;
	game->stage_index = 1;
	game->start_delay = 1;
	game->end_delay = 1;
	game->gravity_count = game->gravity;

	game->is_running = 1;


	OpenAudio(L"Audio\\bounce.mp3", L"bounce");
	OpenAudio(L"Audio\\jump.mp3", L"jump");
	OpenAudio(L"Audio\\dash.mp3", L"dash");
	OpenAudio(L"Audio\\explosion.mp3", L"explosion");

	return 1;
}

void ShutdownGame(Game* game)
{
	DestroyCredit(game->credit);
	DestroyPlayer(game->player);
	UnloadStage(game->stage);
	DestroyTimer(game->timer);
	DestroyRenderer(game->renderer);
}

void RunGame(Game* game)
{
	static float timer = 0.0f;

	ResetTimer(game->timer);

	while (game->is_running)
	{
		TickTimer(game->timer);

		Input(game);

		float delta_time = GetDeltaTime(game->timer);
		timer += delta_time;

		if (timer >= game->update_time)
		{
			Update(game, game->update_time);
			timer = 0.0f;
		}
		
		Render(game);
	}
}

int ReadConfig(Game* game)
{
	FILE* fp = NULL;
	fopen_s(&fp, "config.txt", "r");

	if (!fp)
		return 0;

	char key[16];
	char value[16];

	while (fscanf_s(fp, "%s%s", key, sizeof(key), value, sizeof(value)) != EOF)
	{
		if (strcmp(key, "update-time") == 0)
			game->update_time = strtof(value, NULL);
		else if (strcmp(key, "gravity") == 0)
			game->gravity = strtol(value, NULL, 10);
		else if (strcmp(key, "stage-count") == 0)
			game->stage_count = strtol(value, NULL, 10);
	}

	return 1;
}

void Input(Game* game)
{
	PollKeys();
	const char* keys = GetKeys();

	if (game->is_input)
	{
		if (keys[VK_R])
		{
			CleanGame(game);
			game->state = READY;
			game->stage_index = 1;
		}

		if (keys[VK_PRIOR])
			game->state = CLEAR;

		InputPlayer(game->player, keys);
	}

	if (keys[VK_ESCAPE])
		game->is_running = 0;
}

void Update(Game* game, float delta_time)
{
	switch (game->state)
	{
	case READY:
		ReadyGame(game, delta_time);
		break;
	case PLAYING:
		PlayGame(game, delta_time);
		break;
	case CLEAR:
		ClearGame(game, delta_time);
		break;
	case GAME_OVER:
		break;
	case ENDING:
		UpdateCredit(game->credit, delta_time);
		break;
	}
}

void Render(Game* game)
{
	Renderer* renderer = game->renderer;

	SetRenderDrawColor(renderer, BLACK, BLACK);
	RenderClear(renderer, L' ');

	int width = 0, height = 0;
	GetRenderSize(renderer, &width, &height);

	switch (game->state)
	{
	case READY:
	{
		int width = 0, height = 0;
		GetRenderSize(renderer, &width, &height);

		wchar_t stage_name[16] = { 0 };
		swprintf_s(stage_name, 16, L"Stage %d", game->stage_index);

		SetRenderDrawColor(renderer, GREEN, BLACK);
		RenderDrawText(renderer, stage_name, wcslen(stage_name), width / 2, height / 3, ALIGN_CENTER);
	}
		break;
	case PLAYING:
	case CLEAR:
	case GAME_OVER:
		SetRenderDrawColor(renderer, SKY, BLACK);
		DrawStage(renderer, game->stage);

		if (game->state == PLAYING)
		{
			SetRenderDrawColor(renderer, YELLOW, BLACK);
			DrawPlayer(renderer, game->player);
		}
		else if (game->state == CLEAR)
		{
			const wchar_t* message = L"Stage Clear!";
			SetRenderDrawColor(renderer, BLUE, BLACK);
			RenderDrawText(renderer, message, wcslen(message), width / 2, height / 3, ALIGN_CENTER);
		}
		else
		{
			const wchar_t* message = L"Game Over...";
			SetRenderDrawColor(renderer, RED, BLACK);
			RenderDrawText(renderer, message, wcslen(message), width / 2, height / 3, ALIGN_CENTER);
		}

		SetRenderDrawColor(renderer, YELLOW, BLACK);
		const wchar_t* restart_message = L"다시 시작:R";
		int restart_message_length = wcslen(restart_message);
		RenderDrawText(renderer, restart_message, restart_message_length, 1, height - 1, ALIGN_LEFT);
		const wchar_t* exit_message = L"게임 종료:ESC";
		RenderDrawText(renderer, exit_message, wcslen(exit_message), restart_message_length + 3, height - 1, ALIGN_LEFT);
		break;
	case ENDING:
		SetRenderDrawColor(renderer, WHITE, BLACK);
		RenderCredit(renderer, game->credit);
		break;
	}

	RenderPresent(renderer);
}

void ReadyGame(Game* game, float delta_time)
{
	static float timer = 0.0f;

	if (!game->stage)
	{
		char stage_name[MAX_PATH] = { 0 };
		sprintf_s(stage_name, MAX_PATH, "Stage\\stage%d.txt", game->stage_index);

		game->stage = LoadStage(stage_name);

		Vector2 start_position = GetPlayerStartPosition(game->stage);
		SetPlayerPosition(game->player, start_position.x, start_position.y);
		SetPlayerVelocity(game->player, 0, -1);

		game->is_input = 1;

		timer = 0.0f;
	}

	if (timer < game->start_delay)
		timer += delta_time;
	else
		game->state = PLAYING;
}

void PlayGame(Game* game, float delta_time)
{
	Stage* stage = game->stage;
	Player* player = game->player;

	Vector2 velocity = GetPlayerVelocity(player);
	Vector2 curr_position = GetPlayerPosition(player);
	Vector2 next_position = { curr_position.x + velocity.x, curr_position.y + velocity.y };

	ObjectType object = GetStageAt(stage, next_position.x, next_position.y);
	switch (object)
	{
	case EMPTY:
		SetPlayerPosition(player, next_position.x, next_position.y);
		break;
	case WALL:
	case ROCK:
		if (object == ROCK)
		{
			if (curr_position.y < next_position.y)
				SetStageAt(stage, next_position.x, next_position.y, EMPTY);
		}

		if (GetStageAt(stage, next_position.x, curr_position.y) == EMPTY)
		{
			SetPlayerPosition(player, next_position.x, curr_position.y);
			velocity.y *= -1;
		}
		else if (GetStageAt(stage, curr_position.x, next_position.y) == EMPTY)
		{
			SetPlayerPosition(player, curr_position.x, next_position.y);
			velocity.x *= -1;
			if (velocity.y == 0)
				velocity.y = 1;
		}
		else
		{
			velocity.x *= -1;
			velocity.y *= -1;
		}

		PlayAudio(L"bounce");
		break;
	case JUMP:
		if (curr_position.y < next_position.y)
		{
			velocity.y = -1;
			game->gravity_count = game->gravity + 2;

			PlayAudio(L"jump");
		}
		else
		{
			if (GetStageAt(stage, next_position.x, curr_position.y) == EMPTY)
			{
				SetPlayerPosition(player, next_position.x, curr_position.y);
				velocity.y *= -1;
			}
			else if (GetStageAt(stage, curr_position.x, next_position.y) == EMPTY)
			{
				SetPlayerPosition(player, curr_position.x, next_position.y);
				velocity.x *= -1;
				if (velocity.y == 0)
					velocity.y = 1;
			}
			else
			{
				velocity.x *= -1;
				velocity.y *= -1;
			}
		}
		break;
	case DASH_LEFT:
		if (curr_position.y < next_position.y)
		{
			SetPlayerPosition(player, curr_position.x, next_position.y);
			velocity.x = -1;
			velocity.y = 0;

			PlayAudio(L"dash");
		}
		else
		{
			if (GetStageAt(stage, next_position.x, curr_position.y) == EMPTY)
			{
				SetPlayerPosition(player, next_position.x, curr_position.y);
				velocity.y *= -1;
			}
			else if (GetStageAt(stage, curr_position.x, next_position.y) == EMPTY)
			{
				SetPlayerPosition(player, curr_position.x, next_position.y);
				velocity.x *= -1;
				if (velocity.y == 0)
					velocity.y = 1;
			}
			else
			{
				velocity.x *= -1;
				velocity.y *= -1;
			}
		}
		break;
	case DASH_RIGHT:
		if (curr_position.y < next_position.y)
		{
			SetPlayerPosition(player, curr_position.x, next_position.y);
			velocity.x = 1;
			velocity.y = 0;
			
			PlayAudio(L"dash");
		}
		else
		{
			if (GetStageAt(stage, next_position.x, curr_position.y) == EMPTY)
			{
				SetPlayerPosition(player, next_position.x, curr_position.y);
				velocity.y *= -1;
			}
			else if (GetStageAt(stage, curr_position.x, next_position.y) == EMPTY)
			{
				SetPlayerPosition(player, curr_position.x, next_position.y);
				velocity.x *= -1;
				if (velocity.y == 0)
					velocity.y = 1;
			}
			else
			{
				velocity.x *= -1;
				velocity.y *= -1;
			}
		}
		break;
	case BOMB:
	case INVALID:
		if (object == BOMB)
			PlayAudio(L"explosion");
		game->state = GAME_OVER;
		break;
	case GOAL:
		game->state = CLEAR;
		break;
	}

	// 중력
	if (velocity.y < 0)
	{
		--game->gravity_count;
		if (game->gravity_count < 0)
			velocity.y = 1;
	}
	else
	{
		game->gravity_count = game->gravity;
	}

	SetPlayerVelocity(player, velocity.x, velocity.y);
}

void ClearGame(Game* game, float delta_time)
{
	static float timer = 0.0f;
	if (timer < game->end_delay)
	{
		timer += delta_time;
		game->is_input = 0;
	}
	else
	{
		CleanGame(game);
		
		++game->stage_index;
		if (game->stage_index > game->stage_count)
			game->state = ENDING;
		else
			game->state = READY;

		timer = 0.0f;
	}
}

void CleanGame(Game* game)
{
	UnloadStage(game->stage);
	game->stage = NULL;
}
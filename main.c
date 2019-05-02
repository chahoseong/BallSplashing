#include "timer.h"

#include <conio.h>
#include <locale.h>
#include <stdio.h>
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

typedef enum _ObjectType
{
	GOAL = -1,
	EMPTY = 0,
	WALL = 1,
	ROCK = 2,
} ObjectType;

typedef struct _Vector2
{
	float x, y;
} Vector2;

typedef struct _Player
{
	Vector2 force;
	Vector2 prev_position;
	Vector2 curr_position;
	Vector2 max_force;
} Player;

static Timer* game_timer;
static wchar_t* stage;
static Player* player;
static int is_running;


int main(void)
{
	setlocale(LC_ALL, "");

	// 게임 시계 생성 및 초기화
	game_timer = CreateTimer();
	ResetTimer(game_timer);

	// 스테이지 불러오기
	FILE* fp = NULL;
	fopen_s(&fp, "stage1.txt", "r");

	if (!fp)
		return 0;

	fseek(fp, 0, SEEK_END);
	long stage_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* buffer = (char*)malloc(stage_size);
	fread_s(buffer, stage_size, stage_size, 1, fp);

	stage = (wchar_t*)malloc(sizeof(wchar_t) * 16 * 21);

	// 스테이지 정보를 그림으로 변환
	for (int y = 0; y < 16; ++y)
	{
		for (int x = 0; x < 21; ++x)
		{
			char c = buffer[y * 21 + x];
			int i = c - '0';
			switch (i)
			{
			case GOAL:
			case EMPTY:
				stage[y * 21 + x] = L' ';
				break;
			case WALL:
				stage[y * 21 + x] = L'■';
				break;
			case ROCK:
				stage[y * 21 + x] = L'▥';
				break;
			default:
				stage[y * 21 + x] = L' ';
			}
		}
	}

	free(buffer);

	player = (Player*)malloc(sizeof(Player));
	memset(player, 0, sizeof(Player));

	player->force.y = -300.0f;
	player->curr_position.x = 1;
	player->curr_position.y = 12;

	is_running = 1;

	float test_timer = 0.0f;
	float gravity = 0.98f;

	// 커서 숨기기
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	while (is_running)
	{
		TickTimer(game_timer);


		// 입력
		if (_kbhit())
		{
			int key = _getch();
			
			if (key == KEY_ARROW)
			{
				key = _getch();
				
				int force_x = 0;

				switch (key)
				{
				case KEY_LEFT:
					force_x -= (int)player->max_force.x;
					break;
				case KEY_RIGHT:
					force_x += (int)player->max_force.x;
					break;
				}

				player->force.x = force_x;
			}
			else
			{
				switch (key)
				{
				case KEY_ESC:
					is_running = 0;
					break;
				}
			}
		}

		float delta_time = GetDeltaTime(game_timer);
		// 갱신
		player->force.y += gravity * delta_time;

		Vector2 acceleration = { player->force.x, player->force.y };
		Vector2 velocity = { acceleration.x * delta_time, acceleration.y * delta_time };
		Vector2 next_position = { player->curr_position.x + velocity.x * delta_time,
			player->curr_position.y + 10 * velocity.y * delta_time };

		if ((next_position.x >= 0 && next_position.x < 21) && (next_position.y >= 0 && next_position.y < 16))
		{
			if (stage[(int)(next_position.y * 21 + next_position.x)] == EMPTY)
			{
				player->prev_position = player->curr_position;
				player->curr_position = next_position;
			}
			else
			{
				if (stage[(int)(next_position.y * 21 + next_position.x)] == WALL)
				{
					if (player->force.y > 0)
					{
						player->force.y = -300;
					}
				}
			}
		}

		// 플레이어 그리기
		stage[(int)(player->curr_position.y * 21 + player->curr_position.x)] = L' ';
		stage[(int)(player->curr_position.y * 21 + player->curr_position.x)] = L'●';


		if (test_timer >= 1.0f)
		{
			char log[128];
			sprintf_s(log, 128, "force : (%f, %f), position : (%f, %f), next position : (%f, %f)",
				player->force.x, player->force.y, player->curr_position.x, player->curr_position.y, next_position.x, next_position.y);
			SetConsoleTitleA(log);

			test_timer = 0.0f;
		}
		else
		{
			test_timer += delta_time;
		}


		// 그리기
		COORD cursor_position = { 0, 0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_position);

		for (int y = 0; y < 16; ++y)
		{
			for (int x = 0; x < 21; ++x)
				printf("%2lc", stage[y * 21 + x]);
			printf("%2lc", L'\n');
		}
	}

	free(player);
	free(stage);

	DestroyTimer(&game_timer);

	return 0;
}
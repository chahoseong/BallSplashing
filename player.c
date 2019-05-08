#include "player.h"
#include "game.h"
#include "renderer.h"

#include <math.h>
#include <stdio.h>
#include <Windows.h>

typedef struct Player
{
	Vector2 velocity;
	Vector2 max_velocity;
	Vector2 position;
	int jumping;
	wchar_t rendering_character;
} Player;

Player* CreatePlayer(wchar_t character)
{
	Player* player = (Player*)malloc(sizeof(Player));
	if (!player)
		return NULL;

	memset(player, 0, sizeof(Player));
	player->rendering_character = character;

	return player;
}

void DestroyPlayer(Player* player)
{
	free(player);
}

void SetPlayerVelocity(Player* player, int x, int y)
{
	Vector2 velocity = { x, y };
	player->velocity = velocity;
}

void SetPlayerPosition(Player* player, int x, int y)
{
	Vector2 position = { x, y };
	player->position = position;
}

void SetPlayerMaxVelocity(Player* player, int x, int y)
{
	Vector2 max_velocity = { x, y };
	player->max_velocity = max_velocity;
}

void SetPlayerCharacter(Player* player, wchar_t character)
{
	player->rendering_character = character;
}

Vector2 GetPlayerVelocity(Player* player)
{
	return player->velocity;
}

Vector2 GetPlayerPosition(Player* player)
{
	return player->position;
}

Vector2 GetPlayerMaxVelocity(Player* player)
{
	return player->max_velocity;
}

wchar_t GetPlayerCharacter(Player* player)
{
	return player->rendering_character;
}

void InputPlayer(Player* player, const char* key_state)
{
	if (key_state[VK_LEFT])
	{
		if (player->velocity.y == 0 && player->velocity.x > 0)
			player->velocity.y = 1;

		player->velocity.x += -1;

		if (player->velocity.x < -player->max_velocity.x)
			player->velocity.x = -player->max_velocity.x;
	}
	if (key_state[VK_RIGHT])
	{
		if (player->velocity.y == 0 && player->velocity.x < 0)
			player->velocity.y = 1;

		player->velocity.x += 1;

		if (player->velocity.x > player->max_velocity.x)
			player->velocity.x = player->max_velocity.x;
	}
}

void UpdatePlayer(Player* player, float delta_time)
{
	player->position.x += player->velocity.x;
	player->position.y += player->velocity.y;

	player->jumping = 0;
}

void DrawPlayer(Renderer* renderer, const Player* player)
{
	RenderDraw(renderer, player->rendering_character, (int)player->position.x, (int)player->position.y);
}
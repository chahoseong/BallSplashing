#include "player.h"
#include "game.h"
#include "graphics.h"

#include <stdio.h>
#include <Windows.h>

Player* CreatePlayer()
{
	Player* player = (Player*)malloc(sizeof(Player));
	if (!player)
		return NULL;

	memset(player, 0, sizeof(Player));

	return player;
}

void DestroyPlayer(Player** player)
{
	free(*player);
	*player = NULL;
}

void InputPlayer(Player* player, const char* keys)
{
	int force_x = 0;

	if (keys[VK_LEFT])
		force_x -= (int)player->max_force.x;
	if (keys[VK_RIGHT])
		force_x += (int)player->max_force.x;

	player->force.x = (float)force_x;
}

void UpdatePlayer(Player* player, float delta_time)
{
	Vector2 acceleration = { player->force.x, player->force.y };
	Vector2 velocity = { acceleration.x * delta_time, acceleration.y * delta_time };

	player->prev_position = player->curr_position;

	player->curr_position.x += velocity.x * delta_time;
	player->curr_position.y += velocity.y * delta_time;
}

void RenderPlayer(Player* player)
{
	DrawObject(L" ", player->prev_position);
	DrawObject(L"¡Ü", player->curr_position);
}
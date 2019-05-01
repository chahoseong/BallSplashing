#include "player.h"
#include "game.h"
#include "graphics.h"

#include <stdio.h>
#include <Windows.h>

void InputPlayer(Player* player, char* keys)
{
	int max_force_x = 0;

	if (keys[VK_LEFT])
		max_force_x -= player->max_force.x;
	if (keys[VK_RIGHT])
		max_force_x += player->max_force.x;

	player->max_force.x = max_force_x;
}

void UpdatePlayer(Player* player, float delta_time)
{
	Vector2 acceleration = { player->force.x * delta_time, player->force.y * delta_time };
	Vector2 velocity = { acceleration.x * delta_time, acceleration.y * delta_time };

	player->position.x += velocity.x * delta_time;
	player->position.y += velocity.y * delta_time;
}

void RenderPlayer(Player* player)
{
	WriteFrameBuffer("A", 1, player->position.x, player->position.y);
}
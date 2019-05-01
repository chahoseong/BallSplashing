#pragma once

#include "game.h"

typedef struct PLAYER
{
	Vector2 force;
	Vector2 position;

	Vector2 max_force;
} Player;

void InputPlayer(Player* player, char* keys);
void UpdatePlayer(Player* player, float delta_time);
void RenderPlayer(Player* player);

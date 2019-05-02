#pragma once

#include "game.h"
#include <stdio.h>

typedef struct _Player
{
	Vector2 force;
	Vector2 prev_position;
	Vector2 curr_position;
	Vector2 max_force;
} Player;

Player* CreatePlayer();
void DestroyPlayer(Player** player);

void InputPlayer(Player* player, const char* keys);
void UpdatePlayer(Player* player, float delta_time);
void RenderPlayer(Player* player);

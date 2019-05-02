#pragma once

#include "game.h"
#include <stdio.h>

struct Player;
typedef struct Player Player;

Player* CreatePlayer();
void DestroyPlayer(Player* player);

void InputPlayer(Player* player, const char* keys);
void UpdatePlayer(Player* player, float delta_time);
void RenderPlayer(Player* player);
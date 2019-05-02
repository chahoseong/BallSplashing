#pragma once

#include "game.h"
#include <stdio.h>

struct Player;
typedef struct Player Player;

Player* CreatePlayer();
void DestroyPlayer(Player* player);

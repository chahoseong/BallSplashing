#pragma once

#include "type.h"
#include "renderer.h"

typedef struct Player
{
	Vector2 force;
	Vector2 position;
	wchar_t rendering_character;
} Player;

void DrawPlayer(Renderer* renderer, const Player* player);
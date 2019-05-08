#pragma once

#include "type.h"
#include "renderer.h"
#include "stage.h"

struct Player;
typedef struct Player Player;

Player* CreatePlayer(wchar_t character);
void DestroyPlayer(Player* player);

void SetPlayerVelocity(Player* player, int x, int y);
void SetPlayerPosition(Player* player, int x, int y);
void SetPlayerMaxVelocity(Player* player, int x, int y);
void SetPlayerCharacter(Player* player, wchar_t character);

Vector2 GetPlayerVelocity(Player* player);
Vector2 GetPlayerPosition(Player* player);
Vector2 GetPlayerMaxVelocity(Player* player);
wchar_t GetPlayerCharacter(Player* player);

void InputPlayer(Player* player, const char* key_state);
// void UpdatePlayer(Player* player);
void DrawPlayer(Renderer* renderer, const Player* player);
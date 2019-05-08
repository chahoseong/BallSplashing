#pragma once

#include "type.h"
#include "renderer.h"

typedef enum ObjectType
{
	EMPTY,
	WALL,
	ROCK,
	BOMB,
	JUMP,
	DASH_LEFT,
	DASH_RIGHT,
	INVALID,
	GOAL,
} ObjectType;

struct Stage;
typedef struct Stage Stage;

Stage* LoadStage(const char* filename);
void UnloadStage(Stage* stage);

int GetStageWidth(Stage* stage);
int GetStageHeight(Stage* stage);
Vector2 GetPlayerStartPosition(Stage* stage);

void SetStageAt(Stage* stage, int x, int y, ObjectType type);
ObjectType GetStageAt(Stage* stage, int x, int y);

void DrawStage(Renderer* renderer, Stage* stage);
#include "stage.h"

#include "stage.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stage
{
	ObjectType* data;
	int width;
	int height;
	Vector2 start_position;
} Stage;

Stage* LoadStage(const char* filename)
{
	FILE* fp;
	fopen_s(&fp, filename, "r");

	if (!fp)
		return NULL;

	Stage* stage = (Stage*)malloc(sizeof(Stage));
	if (!stage)
		return NULL;

	fscanf_s(fp, "%d%d", &stage->width, &stage->height);
	fscanf_s(fp, "%d%d", &stage->start_position.x, &stage->start_position.y);

	int total_size = sizeof(ObjectType) * stage->width * stage->height;
	
	stage->data = (ObjectType*)malloc(total_size);
	if (!stage)
		return NULL;

	
	for (int y = 0; y < stage->height; ++y)
	{
		for (int x = 0; x < stage->width; ++x)
		{
			int element;
			
			// 공백 제거
			do
			{
				element = fgetc(fp);
			} while (isspace(element));

			element -= '0';
			int index = y * stage->width + x;

			// stage->data[y * stage->width + x] = (ObjectType)element;
			switch (element)
			{
			case EMPTY:
				stage->data[index] = EMPTY;
				break;
			case WALL:
				stage->data[index] = WALL;
				break;
			case ROCK:
				stage->data[index] = ROCK;
				break;
			case BOMB:
				stage->data[index] = BOMB;
				break;
			case JUMP:
				stage->data[index] = JUMP;
				break;
			case DASH_LEFT:
				stage->data[index] = DASH_LEFT;
				break;
			case DASH_RIGHT:
				stage->data[index] = DASH_RIGHT;
				break;
			case INVALID:
				stage->data[index] = INVALID;
				break;
			case GOAL:
				stage->data[index] = GOAL;
			}
		}
	}

	fclose(fp);

	return stage;
}

void UnloadStage(Stage* stage)
{
	free(stage->data);
	free(stage);
}

int GetStageWidth(Stage* stage)
{
	return stage->width;
}

int GetStageHeight(Stage* stage)
{
	return stage->height;
}

Vector2 GetPlayerStartPosition(Stage* stage)
{
	return stage->start_position;
}

void SetStageAt(Stage* stage, int x, int y, ObjectType type)
{
	stage->data[y * stage->width + x] = type;
}

ObjectType GetStageAt(Stage* stage, int x, int y)
{
	if (x < 0 || x >= stage->width || y < 0 || y >= stage->height)
		return INVALID;

	return stage->data[y * stage->width + x];
}

void DrawStage(Renderer* renderer, Stage* stage)
{
	for (int y = 0; y < stage->height; ++y)
	{
		for (int x = 0; x < stage->width; ++x)
		{
			switch (stage->data[y * stage->width + x])
			{
			case EMPTY:
				RenderDraw(renderer, L' ', x, y);
				break;
			case WALL:
				RenderDraw(renderer, L'■', x, y);
				break;
			case ROCK:
				RenderDraw(renderer, L'▥', x, y);
				break;
			case BOMB:
				RenderDraw(renderer, L'♨', x, y);
				break;
			case JUMP:
				RenderDraw(renderer, L'▣', x, y);
				break;
			case DASH_LEFT:
				RenderDraw(renderer, L'←', x, y);
				break;
			case DASH_RIGHT:
				RenderDraw(renderer, L'→', x, y);
				break;
			}
		}
	}
}
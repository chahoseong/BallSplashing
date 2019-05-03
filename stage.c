#include "stage.h"

#include "stage.h"
#include "object.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stage
{
	Object* data;
	int width;
	int height;
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

	fscanf_s(fp, "%d", &stage->width);
	fscanf_s(fp, "%d", &stage->height);

	int total_size = sizeof(Object) * stage->width * stage->height;
	
	stage->data = (Object*)malloc(total_size);
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

			Object object;
			object.type = element - '0';

			switch (object.type)
			{
			case EMPTY:
				object.rendering_character = L' ';
				break;
			case WALL:
				object.rendering_character = L'■';
				break;
			case ROCK:
				object.rendering_character = L'▥';
				break;
			}

			stage->data[y * stage->width + x] = object;
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

void SetStageAt(Stage* stage, int x, int y, ObjectType type)
{
	stage->data[y * stage->width + x].type = type;

	switch (type)
	{
	case EMPTY:
		stage->data[y * stage->width + x].rendering_character = L' ';
		break;
	case WALL:
		stage->data[y * stage->width + x].rendering_character = L'■';
		break;
	case ROCK:
		stage->data[y * stage->width + x].rendering_character = L'▥';
		break;
	}
}

Object GetStageAt(Stage* stage, int x, int y)
{
	if (x < 0 || x >= stage->width || y < 0 || y >= stage->height)
	{
		Object object;
		object.type = INVALID_OBJECT;
		return object;
	}

	return stage->data[y * stage->width + x];
}

void DrawStage(Renderer* renderer, Stage* stage)
{
	for (int y = 0; y < stage->height; ++y)
	{
		for (int x = 0; x < stage->width; ++x)
			RenderDraw(renderer, stage->data[y * stage->width + x].rendering_character, x, y);
	}
}
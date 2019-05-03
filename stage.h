#pragma once

#include "renderer.h"
#include "object.h"

struct Stage;
typedef struct Stage Stage;

Stage* LoadStage(const char* filename);
void UnloadStage(Stage* stage);

int GetStageWidth(Stage* stage);
int GetStageHeight(Stage* stage);

void SetStageAt(Stage* stage, int x, int y, ObjectType type);
Object GetStageAt(Stage* stage, int x, int y);

void DrawStage(Renderer* renderer, Stage* stage);
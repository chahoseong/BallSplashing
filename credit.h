#pragma once

#include "renderer.h"

struct Credit;
typedef struct Credit Credit;

Credit* CreateCredit(Renderer* renderer, const char* filename);
void DestroyCredit(Credit* credit);

void UpdateCredit(Credit* credit, float delta_time);
void RenderCredit(Renderer* renderer, Credit* credit);
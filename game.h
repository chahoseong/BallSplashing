#pragma once

struct Game;
typedef struct Game Game;

Game* CreateGame();
void DestroyGame(Game* game);

int StartupGame(Game* game);
void ShutdownGame(Game* game);
void RunGame(Game* game);
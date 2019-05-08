#include "game.h"
#include "renderer.h"

#include <stdio.h>
#include <Windows.h>

int main(void)
{
	Game* game = CreateGame();
	if (!game)
	{
		fprintf(stderr, "Failed CreateGame()");
		return 0;
	}

	if (StartupGame(game))
		RunGame(game);
	ShutdownGame(game);

	DestroyGame(game);

	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("���α׷��� ����Ǿ����ϴ�.\n");

	return 0;
}
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
	printf("프로그램이 종료되었습니다.\n");

	return 0;
}
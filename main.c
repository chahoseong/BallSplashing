#include "game.h"

int main(void)
{
	if (Startup())
		GameLoop();
	Shutdown();

	return 0;
}
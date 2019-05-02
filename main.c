#include "timer.h"

int main(void)
{
	Timer* game_timer = CreateTimer();
	ResetTimer(game_timer);
	
	int is_running = 1;

	while (is_running)
	{
		TickTimer(game_timer);
	}


	return 0;
}
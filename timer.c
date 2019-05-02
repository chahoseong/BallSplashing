#include "timer.h"

#include <stdlib.h>
#include <Windows.h>

typedef struct Timer
{
	double seconds_per_count;
	float delta_time;

	__int64 base_time;
	__int64 stop_time;
	__int64 paused_time;
	__int64 prev_time;
	__int64 curr_time;

	int is_stopped;
} Timer;

Timer* CreateTimer()
{
	Timer* timer;

	timer = (Timer*)malloc(sizeof(struct Timer));
	if (!timer)
		return NULL;

	__int64 counts_per_second;
	QueryPerformanceFrequency((LARGE_INTEGER*)&counts_per_second);
	timer->seconds_per_count = 1.0 / counts_per_second;

	return timer;
}

void DestroyTimer(Timer* timer)
{
	free(timer);
}

void Tick(Timer* timer)
{
	if (timer->is_stopped)
	{
		timer->delta_time = 0.0f;
		return;
	}

	__int64 curr_time;
	QueryPerformanceCounter((LARGE_INTEGER*)&curr_time);
	
	timer->curr_time = curr_time;
	timer->delta_time = (float)((timer->curr_time - timer->prev_time) * timer->seconds_per_count);
	timer->prev_time = timer->curr_time;
}

void ResetTimer(Timer* timer)
{
	__int64 curr_time;
	QueryPerformanceCounter((LARGE_INTEGER*)&curr_time);

	timer->base_time = curr_time;
	timer->prev_time = curr_time;
	timer->stop_time = 0;
	timer->is_stopped = 0;
}

void StartTimer(Timer* timer)
{
	if (!timer->is_stopped)
		return;

	__int64 start_time;
	QueryPerformanceCounter((LARGE_INTEGER*)&start_time);

	timer->paused_time += (start_time - timer->stop_time);
	timer->prev_time = start_time;
	timer->stop_time = 0;
	timer->is_stopped = 0;
}

void PauseTimer(Timer* timer)
{
	if (timer->is_stopped)
		return;

	__int64 stop_time;
	QueryPerformanceCounter((LARGE_INTEGER*)&stop_time);

	timer->stop_time = stop_time;
	timer->is_stopped = 1;
}

float GetDeltaTime(Timer* timer)
{
	return timer->delta_time;
}

float GetTotalTime(Timer* timer)
{
	if (timer->is_stopped)
		return (float)(((timer->stop_time - timer->paused_time) - timer->base_time) * timer->seconds_per_count);
	else
		return (float)(((timer->curr_time - timer->paused_time) - timer->base_time) * timer->seconds_per_count);
}
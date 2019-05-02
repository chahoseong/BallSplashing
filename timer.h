#pragma once

typedef struct _Timer
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

const Timer* CreateTimer();
void RemoveTimer(Timer** timer);

void TickTimer(Timer* timer);

void ResetTimer(Timer* timer);
void StartTimer(Timer* timer);
void PauseTimer(Timer* timer);

float GetTotalTime(Timer* timer);
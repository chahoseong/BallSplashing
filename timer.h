#pragma once

struct Timer;
typedef struct Timer Timer;

Timer* CreateTimer();
void DestroyTimer(Timer* timer);

void TickTimer(Timer* timer);

void ResetTimer(Timer* timer);
void StartTimer(Timer* timer);
void PauseTimer(Timer* timer);

float GetDeltaTime(Timer* timer);
float GetTotalTime(Timer* timer);
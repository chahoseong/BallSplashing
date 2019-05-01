#pragma once

// opaque type
typedef void* Timer;

int InitTimer(Timer* new_timer);
void CloseTimer(Timer* timer);

void TickTimer(Timer timer);

void ResetTimer(Timer timer);
void StartTimer(Timer timer);
void PauseTimer(Timer timer);

float DeltaTime(Timer timer);
float TotalTime(Timer timer);
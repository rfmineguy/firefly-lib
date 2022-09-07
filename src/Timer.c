#include "../include/Core/Timer.h"
#include "../include/Core/Window.h"

void StartTimerInterval(Timer *pTimer, long interval) {
  if (!pTimer->running) {
    pTimer->start_time = WindowGetTime();
    pTimer->current_time = pTimer->start_time;
    pTimer->interval = interval;
  }
  pTimer->running = true;
}

void ResetTimer(Timer *pTimer) {
  pTimer->running = false;
  StartTimerInterval(pTimer, pTimer->interval);
}

bool TimerElapsed(Timer *pTimer) {
  pTimer->current_time = WindowGetTime();
  bool elapsed = pTimer->current_time - pTimer->start_time > pTimer->interval;
  if (elapsed) 
    ResetTimer(pTimer);
  return elapsed;
}
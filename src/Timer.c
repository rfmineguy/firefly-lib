#include "../include/Core/Timer.h"
#include "../include/Core/Window.h"

void TimerStartInterval(Timer *pTimer, double interval) {
  TimerStartIntervalEx(pTimer, interval, MILLISECOND);
}

void TimerStartIntervalEx(Timer *pTimer, double interval, TimerUnit unit) {
  pTimer->unit = unit;
  if (!pTimer->running) {
    pTimer->start_time = WindowGetTime();
    pTimer->current_time = pTimer->start_time;
    pTimer->interval = interval;
  }
  pTimer->running = true;
}

void ResetTimer(Timer *pTimer) {
  pTimer->running = false;
  TimerStartInterval(pTimer, pTimer->interval);
}

bool TimerElapsed(Timer *pTimer) {
  pTimer->current_time = WindowGetTime();
  double factor;
  switch (pTimer->unit) {
    case MILLISECOND: factor = 1000;
    break;
    case SECOND: factor = 1;
    break;
    case MINUTE: factor = 1.0/60;
    break;
  }
  bool elapsed = pTimer->current_time - pTimer->start_time > pTimer->interval / factor;
  if (elapsed)
      ResetTimer(pTimer);
  return elapsed;
}
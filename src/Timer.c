#include "../include/Core/Timer.h"
#include "../include/Core/Window.h"

Timer FF_Timer(double interval, TimerUnit unit) {
  return (Timer){
    .start_time = 0, 
    .current_time = 0, 
    .interval = interval, 
    .running = false, 
    .unit = unit
  };
}

void FF_TimerStartIntervalEx(Timer *pTimer, double interval, TimerUnit unit) {
  pTimer->unit = unit;
  if (!pTimer->running) {
    pTimer->start_time = FF_GetTime();
    pTimer->current_time = pTimer->start_time;
    pTimer->interval = interval;
  }
  pTimer->running = true;
}
//Deprecated
void TimerStartInterval(Timer *pTimer, double interval) {
  FF_TimerStartIntervalEx(pTimer, interval, MILLISECOND);
}

void FF_TimerReset(Timer *pTimer) {
  pTimer->running = false;
  FF_TimerStartIntervalEx(pTimer, pTimer->interval, pTimer->unit);
}

bool FF_TimerElapsed(Timer *pTimer) {
  pTimer->current_time = FF_GetTime();
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
      FF_TimerReset(pTimer);
  return elapsed;
}
#include "../include/Core/Timer.h"
#include "../include/Core/Window.h"

Timer FF_Timer(double interval, TimerUnit unit) {
  Timer t;

  t.start_time = 0, 
  t.current_time = 0, 
  t.interval = interval, 
  t.running = false, 
  t.unit = unit;
  
  FF_TimerStart(&t);
  return t;
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

void FF_TimerStart(Timer *pTimer) {
  FF_TimerStartIntervalEx(pTimer, pTimer->interval, pTimer->unit);
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
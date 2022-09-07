#ifndef FL_CORETIMER_H
#define FL_CORETIMER_H
#include <stdbool.h>

typedef enum {
    MILLISECOND, SECOND, MINUTE    
} TimerUnit;

typedef struct {
    double start_time, current_time, interval;
    bool running;
    TimerUnit unit;
} Timer;

void StartTimerInterval(Timer*, double);
void StartTimerIntervalEx(Timer*, double, TimerUnit);
void ResetTimer(Timer*);
bool TimerElapsed(Timer*);

#endif

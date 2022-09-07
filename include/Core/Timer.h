#ifndef FL_CORETIMER_H
#define FL_CORETIMER_H
#include <stdbool.h>

typedef struct {
    double start_time, current_time, interval;
    bool running;
} Timer;

void StartTimerInterval(Timer*, long);
void ResetTimer(Timer*);
bool TimerElapsed(Timer*);

#endif

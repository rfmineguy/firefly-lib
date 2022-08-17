#ifndef FL_CORETIMER_H
#define FL_CORETIMER_H
#include <stdbool.h>

typedef struct {
} Timer;

//Timing functeons (Timing.h)
void StartTimerInterval(Timer*, long);
void ResetTimer(Timer*);
bool TimerElapsed(Timer*);

#endif

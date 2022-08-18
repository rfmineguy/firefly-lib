#ifndef FL_CORETIMER_H
#define FL_CORETIMER_H
#include <stdbool.h>

typedef struct {} Timer;
typedef enum {
    SECOND, MINUTE
} TimerUnit;

void StartTimerInterval(Timer*, long, TimerUnit);
void ResetTimer(Timer*);
bool TimerElapsed(Timer*);

#endif

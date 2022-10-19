#ifndef FL_CORETIMER_H
#define FL_CORETIMER_H
#include <stdbool.h>

// Allows for c++ to link lib
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    MILLISECOND, SECOND, MINUTE    
} TimerUnit;

typedef struct {
    double start_time, current_time, interval;
    bool running;
    TimerUnit unit;
} Timer;

Timer FF_Timer(double, TimerUnit);
void FF_TimerStart(Timer*);
void FF_TimerReset(Timer*);
bool FF_TimerElapsed(Timer*);

#ifdef __cplusplus
}
#endif

#endif
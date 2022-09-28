#ifndef FF_CORE_RANDOM_H
#define FF_CORE_RANDOM_H
#include <stdlib.h>

void FF_RandomSeedTime();
void FF_RandomSeedLong(uint32_t);

//not inclusive
int FF_RandomRangeInt(int, int);
int FF_RandomInt();

float FF_RandomRangeFloat(float, float);
float FF_RandomFloat();

#endif
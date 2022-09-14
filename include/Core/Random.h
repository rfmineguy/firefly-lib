#ifndef FF_CORE_RANDOM_H
#define FF_CORE_RANDOM_H
#include <stdlib.h>

void RandomSeedTime();
void RandomSeedLong(uint32_t);

//not inclusive
int RandomRangeInt(int, int);
int RandomInt();

float RandomRangeFloat(float, float);
float RandomFloat();

#endif
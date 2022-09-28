#include "../include/Core/Random.h"
#include <time.h>

void FF_RandomSeedTime() {
  srand(time(NULL));
}

void FF_RandomSeedLong(uint32_t seed) {
  srand(seed);
}

int FF_RandomRangeInt(int lower, int upper) {
  uint32_t r = arc4random_uniform(upper - lower);
  return r + lower;
}

int FF_RandomInt() {
  return FF_RandomRangeInt(0, 1);
}

float FF_RandomRangeFloat(float lower, float upper) {
  // [0-1] => [0-5] => [5-10]
  double v = ((double)rand()) / (double)RAND_MAX;
  return v * (upper - lower) + lower;
}

float FF_RandomFloat() {
  return FF_RandomRangeFloat(0, 1);
}
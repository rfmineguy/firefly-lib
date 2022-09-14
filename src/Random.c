#include "../include/Core/Random.h"
#include <time.h>

void RandomSeedTime() {
  srand(time(NULL));
}

void RandomSeedLong(uint32_t seed) {
  srand(seed);
}

int RandomRangeInt(int lower, int upper) {
  uint32_t r = arc4random_uniform(upper - lower);
  return r + lower;
}

int RandomInt() {
  return RandomRangeInt(0, 1);
}

float RandomRangeFloat(float lower, float upper) {
  // [0-1] => [0-5] => [5-10]
  double v = ((double)rand()) / (double)RAND_MAX;
  return v * (upper - lower) + lower;
}

float RandomFloat() {
  return RandomRangeFloat(0, 1);
}
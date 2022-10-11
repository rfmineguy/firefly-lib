#include "../include/Core/Random.h"
#include "../include/IO/IO.h"
#include <time.h>
#include <stdarg.h>

#define FF_RandomSet(...) __FF_RandomSet()
#define ARRAY_LEN(x) (sizeof(x) / sizeof(x[0]))

void FF_RandomSeedTime() {
  srand(time(NULL));
}

void FF_RandomSeedLong(uint32_t seed) {
  srand(seed);
}

int FF_RandomRangeInt(int lower, int upper) {
  // [0, upper - lower] => [lower, upper]
  uint32_t r = arc4random_uniform(upper - lower);
  return r + lower;
}

int FF_RandomInt() {
  // [0-1]
  return FF_RandomRangeInt(0, 1);
}

double FF_RandomFromSet(int size, double *arr) {
  int index = FF_RandomRangeInt(0, size);
  return arr[index];
}

float FF_RandomRangeFloat(float lower, float upper) {
  // [0-1] => [0-5] => [5-10]
  double v = ((double)rand()) / (double)RAND_MAX;
  return v * (upper - lower) + lower;
}

float FF_RandomFloat() {
  return FF_RandomRangeFloat(0, 1);
}
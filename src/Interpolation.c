#include "../include/Core/Interpolation.h"
#include <math.h>

double Clamp(double x, double min, double max) {
  if (x < min) {
    x = min;
  }
  if (x > max) {
    x = max;
  }
  return x;
}

double FF_LerpFuncLinear(double a, double b, double t) {
  return b * t + a * (1 - t);  
}

double FF_LerpFuncLinearLog(double a, double b, double t) {
  return log(b) * t + log(a) * (1 - t);  
}

double FF_LerpFuncSmoothstep(double a, double b, double t) {
  return 0;
}

double FF_LerpFuncSlerp(double a, double b, double t) {
  return 0;
}

double FF_LerpFunc(double(*func)(double, double, double), double a, double b, double t) {
  return func(a, b, t);
}
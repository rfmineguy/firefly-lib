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

double FF_Lerp(double a, double b, double t) {
  return b * t + a * (1 - t);  
}

double FF_LerpFunc(LerpFunction func, double a, double b, double t) {
  switch (func) {
  case FF_LINEAR: 
      return FF_Lerp(a, b, t);// b * t + a * (1 - t);
  case FF_SMOOTHSTEP: 
    {
        t = Clamp((t - a) / (a / b), 0.0f, 1.0f);
        return t * t * (3 - 2 * t);
    }
  default: return 0;
  }
}
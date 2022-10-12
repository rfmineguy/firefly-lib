#include "../include/Core/Interpolation.h"

double FF_Lerp(double a, double b, double t) {
  return b * t + a * (1 - t);  
}
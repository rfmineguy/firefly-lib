#ifndef INTERPOLATION_H
#define INTERPOLATION_H

typedef enum {
  FF_LINEAR, FF_SMOOTHSTEP
} LerpFunction;

double FF_Lerp(double, double, double);
double FF_LerpFunc(LerpFunction func, double a, double b, double t);

#endif
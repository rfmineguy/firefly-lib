#ifndef INTERPOLATION_H
#define INTERPOLATION_H

typedef enum {
  FF_LINEAR, FF_SMOOTHSTEP
} LerpFunction;

double FF_LerpFuncLinear(double, double, double);
double FF_LerpFuncLinearLog(double, double, double);
double FF_LerpFuncSmoothstep(double, double, double);
double FF_LerpFuncSlerp(double, double, double);
double FF_LerpFunc(double(*)(double, double, double), double, double, double);

#endif
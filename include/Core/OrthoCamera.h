#ifndef FF_CORE_ORTHOCAM_H
#define FF_CORE_ORTHOCAM_H
#include "Camera.h"

Camera FF_OrthoCamera();
void FF_OrthoCameraUpdate(Camera*);
void FF_OrthoCameraUpdateProj(Camera*, int, int);

#endif
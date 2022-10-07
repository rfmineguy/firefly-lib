#ifndef FF_CORE_PERSPCAM_H
#define FF_CORE_PERSPCAM_H
#include "Camera.h"

Camera FF_PerspectiveCamera();
void FF_PerspectiveCameraUpdate(Camera*);
void FF_PerspectiveCameraUpdateProj(Camera*, int, int);

#endif
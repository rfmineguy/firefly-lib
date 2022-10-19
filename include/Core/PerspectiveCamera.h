#ifndef FF_CORE_PERSPCAM_H
#define FF_CORE_PERSPCAM_H
#include "Camera.h"

#ifdef __cplusplus
extern "C" {
#endif

Camera FF_PerspectiveCamera();
void FF_PerspectiveCameraUpdate(Camera*);
void FF_PerspectiveCameraUpdateProj(Camera*, int, int);
void FF_PerspectiveCameraPrintValues(Camera*);

#ifdef __cplusplus
}
#endif

#endif
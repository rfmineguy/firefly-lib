#ifndef FF_CORE_ORTHOCAM_H
#define FF_CORE_ORTHOCAM_H
#include "Camera.h"

// Allows for c++ to link lib
#ifdef __cplusplus
extern "C" {
#endif

Camera FF_OrthoCamera();
void FF_OrthoCameraUpdate(Camera*, bool);
void FF_OrthoCameraUpdateProj(Camera*, int, int);

#ifdef __cplusplus
}
#endif

#endif
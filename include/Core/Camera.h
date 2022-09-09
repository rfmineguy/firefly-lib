#ifndef FL_CORE_CAMERA_H
#define FL_CORE_CAMERA_H
#include "../../libs/cglm/include/cglm/cglm.h"
#include "../../libs/cglm/include/cglm/cam.h"

typedef struct _Camera {
  vec3 camPos;
  vec3 camTarget;
  vec3 up;
  vec3 camRight;
  vec3 camUp;
  vec3 worldUp;
  vec3 camFront;
  
  mat4 view;
  mat4 proj;
  
  bool isOrtho;
  float fov;
  vec2 size;
} Camera;

void InitCameraOrtho(Camera*);
void InitCameraIso(Camera*);

void UpdateCamera(Camera*);
void RecalcCamera(Camera*);
void UpdateProjectionCamera(Camera*, int, int);

#endif
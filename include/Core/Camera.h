#ifndef FL_CORE_CAMERA_H
#define FL_CORE_CAMERA_H
#include <cglm/cglm.h>
#include <cglm/cam.h>

typedef struct _Camera {
  vec3 camPos;
  vec3 camTarget;
  vec3 camDirection;
  vec3 up;
  vec3 camRight;
  vec3 camUp;
  vec3 camFront;
  
  mat4 view;
  mat4 proj;
  
  bool isOrtho;
} Camera;

void InitCameraOrtho(Camera*);
void InitCameraIso(Camera*);

void UpdateCamera(Camera*);
void RecalcCamera(Camera*);

#endif
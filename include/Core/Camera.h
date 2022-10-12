#ifndef FL_CORE_CAMERA_H
#define FL_CORE_CAMERA_H
#include <cglm/cglm.h>
#include <cglm/cam.h>

typedef enum _ProjectionType {
  ORTHOGRAPHIC, PERSPECTIVE
} ProjectionType;

typedef struct _Camera {
  vec3 camPos;
  vec3 camTarget;
  vec3 camRight;
  vec3 camUp;
  vec3 worldUp;
  vec3 camFront;
  
  mat4 view;
  mat4 proj;
  
  float fov;
  vec2 size;
  
  ProjectionType projection_type;
} Camera;

#endif
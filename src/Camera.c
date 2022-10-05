#include "../include/Core/Camera.h"
#include "../include/Core/Input.h"
#include "../include/IO/Log.h"
#include <string.h>

void UpdateCameraVectors(Camera* pCamera) {
  vec3 front;
  Input* i = FF_int_GetInputPtr();
  front[0] = cos(glm_rad(i->yaw)) * cos(glm_rad(i->pitch));
  front[1] = sin(glm_rad(i->pitch));
  front[2] = sin(glm_rad(i->yaw)) * cos(glm_rad(i->pitch));
  
  glm_vec3_normalize_to(front, pCamera->camFront);
  
  vec3 crossFrontUp;
  glm_cross(pCamera->camFront, pCamera->worldUp, crossFrontUp);
  glm_normalize_to(crossFrontUp, pCamera->camRight);
  
  vec3 crossRightFront;
  glm_cross(pCamera->camRight, pCamera->camFront, crossRightFront);
  glm_normalize_to(crossRightFront, pCamera->camUp);
}

void SetDefaultParams(Camera* pCamera) {
  pCamera->fov = 45.f;
  glm_vec2_copy((vec2){600, 600}, pCamera->size);
  glm_vec3_copy((vec3){0, 0, 20}, pCamera->camPos);
  glm_vec3_copy((vec3){0, 0, 0}, pCamera->camTarget);
  glm_vec3_copy((vec3){0, 1, 0}, pCamera->worldUp);
  glm_vec3_copy((vec3){0, 0, 0}, pCamera->camRight);
  glm_vec3_copy((vec3){0, 1, 0}, pCamera->camUp);
  glm_vec3_copy((vec3){0, 0, -1}, pCamera->camFront);
}

void UpdateCameraProj(Camera* pCamera, int width, int height) {
  pCamera->size[0] = width;
  pCamera->size[1] = height;
  switch (pCamera->projection_type) {
    case ORTHOGRAPHIC: {
      LOG_INFO("Orthographic");
      glm_ortho(0, pCamera->size[0], 0, pCamera->size[1], -1.0f, 1.0f, pCamera->proj);
      break;
    }
    case PERSPECTIVE: {
      LOG_INFO("Perspective");
      glm_perspective(glm_rad(pCamera->fov), pCamera->size[0] / pCamera->size[1], 0.1f, 100.f, pCamera->proj);
      UpdateCameraVectors(pCamera);
      break;
    }
  }
}

Camera FF_OrthoCamera() {
  Camera c;
  c.projection_type = ORTHOGRAPHIC;
  SetDefaultParams(&c);
  UpdateCameraProj(&c, 600, 600);
  return c;
}

Camera FF_PerspectiveCamera() {
  Camera c;
  c.projection_type = PERSPECTIVE;
  SetDefaultParams(&c);
  UpdateCameraProj(&c, 600, 600);
  return c;
}

void InitCamera(Camera* pCamera, ProjectionType type) {
  pCamera->projection_type = type;
  SetDefaultParams(pCamera);
  UpdateCameraProj(pCamera, 600, 600);
}

void UpdateCamera(Camera *pCamera) {
  RecalcCamera(pCamera);
  const float camSpeed = 0.05f;
  if (FF_IsKeyDown(KEY_W)) {
    glm_vec3_muladds(pCamera->camFront, camSpeed, pCamera->camPos);  //?
  }
  if (FF_IsKeyDown(KEY_S)) {
    glm_vec3_muladds(pCamera->camFront, -camSpeed, pCamera->camPos); //?
  }
  if (FF_IsKeyDown(KEY_A)) {
    vec3 cross;
    glm_vec3_cross(pCamera->camFront, pCamera->camUp, cross);
    glm_normalize(cross);
    glm_vec3_muladds(cross, -camSpeed, pCamera->camPos);
  }
  if (FF_IsKeyDown(KEY_D)) {
    vec3 cross;
    glm_vec3_cross(pCamera->camFront, pCamera->camUp, cross);
    glm_normalize(cross);
    glm_vec3_muladds(cross, camSpeed, pCamera->camPos);
  }
  Vec2f scrollDir = FF_GetScrollDirection();
  pCamera->fov += scrollDir.y;
  if (FF_IsScroll())
    UpdateProjectionCamera(pCamera, pCamera->size[0], pCamera->size[1]);
  if (pCamera->fov < 1.f) {
    pCamera->fov = 1.f;
  }
  if (pCamera->fov > 45.f) {
    pCamera->fov = 45.f;
  }
  UpdateCameraVectors(pCamera);
}

void RecalcCamera(Camera *pCamera) {
  vec3 posPlusFront;
  glm_vec3_add(pCamera->camPos, pCamera->camFront, posPlusFront);
  glm_lookat(pCamera->camPos, posPlusFront, pCamera->camUp, pCamera->view);
}

void UpdateProjectionCamera(Camera *pCamera, int width, int height) {
  pCamera->size[0] = width;
  pCamera->size[1] = height;
  LOG_INFO("Resizing projection matrix to {w:%d, h:%d}", width, height);
  glm_perspective(glm_rad(pCamera->fov), (float)width/(float)height, 0.1f, 100.f, pCamera->proj);
  UpdateCameraVectors(pCamera);
}
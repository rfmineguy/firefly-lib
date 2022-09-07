#include "../include/Core/Camera.h"
#include "../include/Core/Input.h"
#include "../include/IO/Log.h"
#include <string.h>

void UpdateCameraVectors(Camera* pCamera) {
  vec3 front;
  Input* i = GetInputPtr();
  front[0] = cos(glm_rad(i->yaw)) * cos(glm_rad(i->pitch));
  front[1] = sin(glm_rad(i->pitch));
  front[2] = sin(glm_rad(i->yaw)) * cos(glm_rad(i->pitch));
  
  glm_vec3_normalize_to(front, pCamera->camFront);
  
  vec3 crossFrontUp;
  glm_cross(pCamera->camFront, pCamera->up, crossFrontUp);
  glm_normalize_to(crossFrontUp, pCamera->camRight);
  
  vec3 crossRightFront;
  glm_cross(pCamera->camRight, pCamera->camFront, crossRightFront);
  glm_normalize_to(crossRightFront, pCamera->camUp);
}

void InitCameraIso(Camera* pCamera) {
  pCamera->isOrtho = false;

  glm_vec3_copy((vec3){0, 0, 3}, pCamera->camPos);
  glm_vec3_copy((vec3){0, 0, 0}, pCamera->camTarget);
  glm_vec3_copy((vec3){0, 1, 0}, pCamera->up);
  glm_vec3_copy((vec3){0, 0, 0}, pCamera->camRight);
  glm_vec3_copy((vec3){0, 1, 0}, pCamera->camUp);
  glm_vec3_copy((vec3){0, 0, -1}, pCamera->camFront);

  glm_perspective(glm_rad(45.f), (float)600/(float)600, 0.1f, 100.f, pCamera->proj);
  UpdateCameraVectors(pCamera);
}

void InitCameraOrtho(Camera* pCamera) {
  pCamera->isOrtho = true;
}

void UpdateCamera(Camera *pCamera) {
  RecalcCamera(pCamera);
  const float camSpeed = 0.05f;
  if (IsKeyDown(KEY_W)) {
    glm_vec3_muladds(pCamera->camFront, camSpeed, pCamera->camPos);  //?
  }
  if (IsKeyDown(KEY_S)) {
    glm_vec3_muladds(pCamera->camFront, -camSpeed, pCamera->camPos); //?
  }
  if (IsKeyDown(KEY_A)) {
    vec3 cross;
    glm_vec3_cross(pCamera->camFront, pCamera->camUp, cross);
    glm_normalize(cross);
    glm_vec3_muladds(cross, -camSpeed, pCamera->camPos);
  }
  if (IsKeyDown(KEY_D)) {
    vec3 cross;
    glm_vec3_cross(pCamera->camFront, pCamera->camUp, cross);
    glm_normalize(cross);
    glm_vec3_muladds(cross, camSpeed, pCamera->camPos);
  }
  UpdateCameraVectors(pCamera);
}

void RecalcCamera(Camera *pCamera) {
  vec3 posPlusFront;
  glm_vec3_add(pCamera->camPos, pCamera->camFront, posPlusFront);
  glm_lookat(pCamera->camPos, posPlusFront, pCamera->up, pCamera->view);
}

void UpdateProjectionCamera(Camera *pCamera, int width, int height) {
  LOG_INFO("Resizing projection matrix to {w:%d, h:%d}", width, height);
  glViewport(0, 0, width, height);
  glm_perspective(glm_rad(45.f), (float)width/(float)height, 0.1f, 100.f, pCamera->proj);
  UpdateCameraVectors(pCamera);
}
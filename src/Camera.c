#include "../include/Core/Camera.h"
#include "../include/Core/Input.h"
#include "../include/IO/Log.h"
#include <string.h>

void InitCameraIso(Camera* pCamera) {
  pCamera->isOrtho = false;

  glm_vec3_copy((vec3){3, 3, 3}, pCamera->camPos);
  glm_vec3_copy((vec3){0, 0, 0}, pCamera->camTarget);
  glm_vec3_copy((vec3){0, 0, 0}, pCamera->camDirection);
  glm_vec3_copy((vec3){0, 1, 0}, pCamera->up);
  glm_vec3_copy((vec3){0, 0, 0}, pCamera->camRight);
  glm_vec3_copy((vec3){0, 1, 0}, pCamera->camUp);
  glm_vec3_copy((vec3){0, 0, -1}, pCamera->camFront);

  glm_vec3_sub(pCamera->camPos, pCamera->camTarget, pCamera->camDirection);
  glm_vec3_normalize_to(pCamera->camDirection, pCamera->camDirection);                  //calculate normalized camera direction
  
  glm_vec3_crossn(pCamera->up, pCamera->camDirection, pCamera->camRight);          //calculate normalized camera right vector
  glm_vec3_cross(pCamera->camDirection, pCamera->camRight, pCamera->camUp);        //calculate camera up vector
  
  glm_mat4_identity(pCamera->view);
  glm_lookat(pCamera->camPos, pCamera->camTarget, pCamera->up, pCamera->view);
  
  glm_perspective(glm_rad(45.f), (float)600/(float)600, 0.1f, 100.f, pCamera->proj);
}

void InitCameraOrtho(Camera* pCamera) {
  pCamera->isOrtho = true;
}

void UpdateCamera(Camera *pCamera) {
  const float camSpeed = 0.5f;
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
}

void RecalcCamera(Camera *pCamera) {
  glm_lookat(pCamera->camPos, pCamera->camTarget, pCamera->up, pCamera->view);
}
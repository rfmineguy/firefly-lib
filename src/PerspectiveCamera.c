#include "../include/Core/PerspectiveCamera.h"
#include "../include/Core/Input.h"
#include "../include/IO/Log.h"

void FF_PerspectiveCameraUpdateCameraVectors(Camera* pCamera) {
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

void FF_PerspectiveCameraUpdateProj(Camera camera, int width, int height) {
  camera.size[0] = width;
  camera.size[1] = height;
  glm_perspective(glm_rad(camera.fov), (float)camera.size[0] / (float)camera.size[1], 0.1f, 100.0f, camera.proj);
}

Camera FF_PerpsectiveCamera() {
  Camera c;
  c.projection_type = PERSPECTIVE;
  c.fov = 45.f;
  glm_vec2_copy((vec2){600, 600}, c.size);
  glm_vec3_copy((vec3){0, 0, 20}, c.camPos);
  glm_vec3_copy((vec3){0, 1, 0}, c.worldUp);
  glm_vec3_copy((vec3){0, 0, 0}, c.camRight);
  glm_vec3_copy((vec3){0, 1, 0}, c.camUp);
  glm_vec3_copy((vec3){0, 0, -1}, c.camFront);
  FF_PerspectiveCameraUpdateCameraVectors(&c);
  return c;
}

void FF_PerspectiveCameraUpdate(Camera* camera) {
  FF_PerspectiveCameraUpdateCameraVectors(camera);
  glm_mat4_identity(camera->view);
  vec3 posPlusFront;
  glm_vec3_add(camera->camPos, camera->camFront, posPlusFront);
  glm_lookat(camera->camPos, posPlusFront, camera->camUp, camera->view);
  
  const float camSpeed = 0.05f;
  if (FF_IsKeyDown(KEY_W)) {
    LOG_DEBUG("Move forward");
    //camera.camPos += camera.camFront * camSpeed;
    glm_vec3_muladds(camera->camFront, camSpeed, camera->camPos);  //?
  }
  if (FF_IsKeyDown(KEY_S)) {
    LOG_DEBUG("Move backward");
    //camera->camPos += camera->camFront * -camSpeed;
    glm_vec3_muladds(camera->camFront, -camSpeed, camera->camPos); //?
  }
  if (FF_IsKeyDown(KEY_A)) {
    LOG_DEBUG("Move left");
    vec3 cross;
    glm_vec3_cross(camera->camFront, camera->camUp, cross);
    glm_normalize(cross);
    glm_vec3_muladds(cross, -camSpeed, camera->camPos);
  }
  if (FF_IsKeyDown(KEY_D)) {
    LOG_DEBUG("Move right");
    vec3 cross;
    glm_vec3_cross(camera->camFront, camera->camUp, cross);
    glm_normalize(cross);
    glm_vec3_muladds(cross, camSpeed, camera->camPos);
  }
}
